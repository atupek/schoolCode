/* Ann Tupek
 * CS631
 * project bison
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include "maps.cpp"
#include <iostream>
#include <string>
extern "C" int yylex();
extern FILE *yyin;
void parseFile(char *fileName);
void yyerror(char *s);
%}

%union{
	char *str;
}

%token NUMBER ATOM VARIABLE QRY IMP COM OBRK CBRK IS
%token ADD SUB MUL DIV OP CP SC DOT CONS

%type <str> predicate factStructure relationStructure ruleStructure queryStructure checkStructure enterFile
%type <str> ATOM NUMBER VARIABLE IS QRY IMP COM OBRK CBRK ADD SUB MUL DIV OP CP SC DOT

%%

metaprogram: programList
|
;

programList: program
| programList program
;

program: predicate
;

predicate: enterFile
| factStructure
| relationStructure
| queryStructure
| ruleStructure
| checkStructure
;

enterFile: CONS OBRK ATOM CBRK
	{parseFile($3);}
;

factStructure: ATOM OP ATOM CP DOT
	{setSingleFact($1, $3);
		Rule rule; rule.arg1 = "X"; rule.arg2="Y"; rule.addFact($1, "X");
		rules[$1]= rule;}
;

relationStructure: ATOM OP ATOM COM ATOM CP DOT
	{setRelateFact($1, $3, $5);
		Rule rule; rule.arg1 = "X"; rule.arg2="Y"; rule.addRelation($1, "X", "Y");
		rules[$1]= rule;}
;

queryStructure: QRY ATOM OP VARIABLE COM ATOM CP DOT
	{setQuery($2, $4, $6);}
| QRY ATOM OP VARIABLE CP DOT
	{queryFact($2, $4);}
;

ruleStructure: ATOM OP VARIABLE COM VARIABLE CP IMP argumentList DOT
	{Rule rule; rule.arg1 = $3; rule.arg2=$5; rules[$1]=rule;
		insertFacts($1); insertRelations($1);}
;

checkStructure: QRY ATOM OP ATOM CP DOT
	{checkFact($2, $4);}
| QRY ATOM OP ATOM COM ATOM CP DOT
	{checkRelation($2, $4, $6);}
;

argumentList: argument
| argumentList COM argument
;

argument: factArgument
| relationArgument
;

factArgument: ATOM OP VARIABLE CP
	{saveFact($1, $3);}
;

relationArgument: ATOM OP VARIABLE COM VARIABLE CP
	{saveRelation($1, $3, $5);}
;

%%

int main(int argc, char **argv)
{
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
