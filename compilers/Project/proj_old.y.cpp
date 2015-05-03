/* Ann Tupek
 * CS631
 * project bison
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include "maps.cpp"
extern "C" int yylex();
void yyerror(char *s);
%}

%union{
	int intval;
	char *strval;
}

%type <strval> term

%token NUMBER ATOM VARIABLE QRY IMP COM OBRK CBRK IS
%token ADD SUB MUL DIV OP CP SC DOT

%%

metaprogram: program;

program: clauseList query {printf("program");}
| query {printf("query");}
| list {printf("list");}
| ATOM IS ATOM {printf("is"); printToken("cheese");}
;

clauseList: clause
| clauseList clause
;

clause: predicate DOT
| predicate IMP predicateList DOT
;

predicateList: predicate
| predicateList COM predicate
;

predicate: ATOM
| structure
;

termList: term
| termList COM term
;

term: NUMBER
| ATOM
| VARIABLE
| structure
| list
;

structure: ATOM OP termList CP
;

list: OBRK predicateList CBRK
;

query: QRY predicateList DOT
;

%%

int main(int argc, char **argv)
{
	yyparse();
	return 0;
}

void yyerror(char *s)
{
	fprintf(stderr, "error: %s ...exiting.\n", s);
}
