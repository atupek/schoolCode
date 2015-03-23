/* Ann Tupek
 * CS631
 * HW2 bison
*/
%{
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
%}

%token NUMBER
%token ADD SUB MUL DIV ABS OP CP SC

%%

stmt: stmt expr SC {printf("statment= %d\n", $2);}
|expr SC {printf("statement= %d\n", $1);}
;

expr: expr ADD term {$$ = $1 + $3; }
| expr SUB term {$$ = $1 - $3;}
| term
;

term: term MUL factor {$$ = $1 * $3;}
| term DIV factor {$$ = $1 / $3;}
| factor
;

factor: digit {$$ = $1;}
| OP expr CP {$$ = $2;}
;

digit: NUMBER {$$ = $1;}
;

%%

main(int argc, char **argv)
{
	/* Test cases without syntax errors
	give the expected results*/
	printf("TEST CASES\n");
	yyin = fopen("testCases.txt", "r");
	yyparse();

	/* Test cases w errors exit after the first
	sytnax error, so it doesn't go through all
	the test cases in the file*/
	printf("TEST CASES WITH ERRORS\n");
	yyin = fopen("testCasesWErrors.txt", "r");
	yyparse();
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s ...exiting.\n", s);
}