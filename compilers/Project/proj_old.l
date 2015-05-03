/* Ann Tupek
 * CS631
 * project flex
*/
%{
# include "proj.tab.h"
extern "C"
    {
        int yylex(void);
    }
%}

%%
"+" {printf("plus "); return ADD;}
"-" {printf("minus "); return SUB;}
"*" {printf("times "); return MUL;}
"/" {printf("divide "); return DIV;}
"(" {printf("open "); return OP;}
")" {printf("close "); return CP;}
";" {printf("semi "); return SC;}
"." {printf("dot "); return DOT;}
"?-" {printf("query "); return QRY;}
":-" {printf("implies "); return IMP;}
"," {printf("comma "); return COM;}
"[" {printf("OBracket "); return OBRK;}
"]" {printf("CBracket "); return CBRK;}
"is" {printf("is "); return IS;}
[a-z]+([a-z]|[A-Z]|[0-9])*|"'"([a-z]|[A-Z]|[0-9])*"'" {printf("atom "); yylval.strval = strdup(yytext); return ATOM;}
[A-Z_]+([a-z]|[A-Z_]|[0-9])* {printf("variable "); ; yylval.strval = strdup(yytext); return VARIABLE;}
[0-9]+ {printf("number "); ; yylval.strval = strdup(yytext); return NUMBER;}
[ \t] {/* ignore whitespace */}
. {printf("Mystery character %c\n", *yytext);}
%%
