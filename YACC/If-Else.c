//lex.l
%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval=atoi(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
\n          { return '\n'; }
[ \t]       ;
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}


//yacc.y
%{
#include<stdio.h>
#include<stdlib.h>

void yyerror(char *s);
int yylex();
%}

%token NUMBER

%%

stmt :
      IF '(' expr ')' stmt
    | IF '(' expr ')' stmt ELSE stmt
    | ID '=' expr ';'
    ;

%%

int main()
{
    printf("Enter expression : ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

int yywrap()
{
    return 1;
}
