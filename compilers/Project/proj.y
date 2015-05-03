/* Ann Tupek
 * CS631
 * project bison
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include "maps.cpp"
extern "C" int yylex();
//YY_BUFFER_STATE bp;
extern FILE *yyin;
void parseFile(char *fileName);
void yyerror(char *s);
%}

%union{
	char *str;
}

%token NUMBER ATOM VARIABLE QRY IMP COM OBRK CBRK IS
%token ADD SUB MUL DIV OP CP SC DOT CONS

%type <str> term structure list predicateList predicate factStructure relationStructure ruleStructure queryStructure enterFile ATOM NUMBER VARIABLE IS QRY IMP COM OBRK CBRK ADD SUB MUL DIV OP CP SC DOT

%%

metaprogram: programList
|
;

programList: program
| programList program
;

program: predicate
| clauseList query{printf("program");}
| query {printf("query");}
| list {printf("list");}
| ATOM IS ATOM {printf("is"); printToken($3);}
;

clauseList: clause
| clauseList clause
;

clause: predicate DOT
| predicate IMP predicateList DOT
;

predicateList: predicate
| predicateList predicate
;

predicate: ATOM
| enterFile
| factStructure
| relationStructure
//| relationList
| queryStructure
| ruleStructure
//| checkStructure
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

enterFile: CONS OBRK ATOM CBRK
	{parseFile($3);}
;

factStructure: ATOM OP ATOM CP DOT
	{setSingleFact($1, $3);
		Rule rule; rule.arg1 = "X"; rule.arg2="Y"; rule.addFact($1, "X");
		rules[$1]= rule;}
;

//relationList: relationStructure
//| relationList relationStructure
//;

relationStructure: ATOM OP ATOM COM ATOM CP DOT
	{setRelateFact($1, $3, $5);
		Rule rule; rule.arg1 = "X"; rule.arg2="Y"; rule.addRelation($1, "X", "Y");
		rules[$1]= rule;}
;

queryStructure: QRY ATOM OP VARIABLE COM ATOM CP DOT
	{setQuery($2, $4, $6);}
| QRY ATOM OP VARIABLE CP DOT
	{queryFact($2, $4);}
//	| QRY ATOM OP ATOM CP DOT
//	{checkFact($2, $4);}
;

ruleStructure: ATOM OP VARIABLE COM VARIABLE CP IMP argumentList DOT
	{Rule rule; rule.arg1 = $3; rule.arg2=$5; rules[$1]=rule; setCurrentString($1); printf("RULE SET");}
;

//checkStructure: QRY ATOM OP ATOM CP DOT
//	{checkFact($2, $4); printf("i'd like to check a fact...");}
//;

argumentList: argument
| argumentList COM argument
;

argument: factArgument
| relationArgument
;

factArgument: ATOM OP VARIABLE CP
	{rules[currentString].addFact($1, $3); printf("FACT ADDED TO RULE");}
;

relationArgument: ATOM OP VARIABLE COM VARIABLE CP
	{rules[currentString].addRelation($1, $3, $5); printf("RELATION ADDED TO RULE");}
;

list: OBRK predicateList CBRK
;

query: QRY predicateList DOT
;

%%

int main(int argc, char **argv)
{
	//setFacts();
	//setRule1();
	//setRule5();
	yyparse();
	return 0;
}

void parseFile(char *fileName)
{
	char fileType[] = ".txt";
	char *file = new char[std::strlen(fileName)+std::strlen(fileType)+1];
	std::strcpy(file, fileName);
	std::strcat(file, fileType);
	yyin = fopen(file, "r");
	yyparse();
}

void yyerror(char *s)
{
	fprintf(stderr, "error: %s ...exiting.\n", s);
}
