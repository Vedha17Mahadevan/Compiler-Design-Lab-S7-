//lex.l
%{
#include "y.tab.h"
#include <string.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*    { return ID; }
\n                        { return '\n'; }
[ \t]                     ;
.                         { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}

//parser.y
%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token ID

%%

stmt :
      ID '\n' { printf("Valid Identifier\n"); }
      ;

%%

int main()
{
    printf("Enter Identifier : ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Identifier\n");
}

int yywrap()
{
    return 1;
}
