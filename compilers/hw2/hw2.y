%{
#include <stdio.h>
%}

%token NUMBER
%token ADD SUB MUL DIV ABS OP CP SC

%%

stmt: expr SC {printf("expr= %d\n", $1);}
;

expr: term exprRest {$$ = $2; printf("expr= %d\n", $$);}
;

exprRest: ADD term exprRest {$$ = $1 + $2; printf("exprRest= %d\n", $$)}
| SUB term exprRest {$$ = $1 - $2;}
| /*empty string*/
;

term: factor termRest { $$ = $1; printf("term= %d\n", $$);}
;

termRest: MUL factor termRest {$$ = $1 * $2; printf("termRest= %d\n", $$);}
| DIV factor termRest {$$ = $1 / $2;}
| /*empty string */
;

factor: NUMBER {$$ = $1; printf("number = %d\n", $1);}
| OP expr CP {$$ = $1;}
;

%%

main(int argc, char **argv)
{
	yyparse();
}

yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}