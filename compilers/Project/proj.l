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

%option noyywrap

%%
"+" {yylval.str = strdup(yytext); return ADD;}
"-" {yylval.str = strdup(yytext); return SUB;}
"*" {yylval.str = strdup(yytext); return MUL;}
"/" {yylval.str = strdup(yytext); return DIV;}
"(" {yylval.str = strdup(yytext); return OP;}
")" {yylval.str = strdup(yytext); return CP;}
";" {yylval.str = strdup(yytext); return SC;}
"." {yylval.str = strdup(yytext); return DOT;}
"?-" {yylval.str = strdup(yytext); return QRY;}
":-" {yylval.str = strdup(yytext); return IMP;}
"," {yylval.str = strdup(yytext); return COM;}
"[" {yylval.str = strdup(yytext); return OBRK;}
"]" {yylval.str = strdup(yytext); return CBRK;}
"is" {yylval.str = strdup(yytext); return IS;}
"consult" {yylval.str = strdup(yytext); return CONS;}
[a-z]+([a-z]|[A-Z]|[0-9])*|"'"([a-z]|[A-Z]|[0-9])*"'" {yylval.str = strdup(yytext); return ATOM;}
[A-Z_]+([a-z]|[A-Z_]|[0-9])* {yylval.str = strdup(yytext); return VARIABLE;}
[0-9]+ {yylval.str = strdup(yytext); return NUMBER;}
[ \t\n] {/* ignore whitespace */}
. {printf("Mystery character %c\n", *yytext);}
<<EOF>> {yyin = stdin; yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE)); yyparse();}
%%
