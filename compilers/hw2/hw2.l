%{
# include "hw2.tab.h"
%}

%%
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"(" {return OP;}
")" {return CP;}
";" {return SC;}
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[ \t] {/* ignore whitespace */}
. {printf("Mystery character %c\n", *yytext);}
%%
