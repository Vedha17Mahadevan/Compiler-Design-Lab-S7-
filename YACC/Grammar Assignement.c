//lex.l
%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]*    { return ID; }
[0-9]+                  { return NUMBER; }
=                       { return '='; }
\+                      { return '+'; }
\n                      { return '\n'; }
[ \t]                   ;
.                       { return yytext[0]; }
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

%token ID NUMBER

%%

stmt :
      ID '=' expr '\n'
      {
          printf("Accepted\n");
      }
      ;

expr :
      expr '+' term
    | term
    ;

term :
      ID
    | NUMBER
    ;

%%

int main()
{
    printf("Enter Assignment : ");
    yyparse();
    return 0;
}

void yyerror(char *s)
{
    printf("Rejected\n");
}

int yywrap()
{
    return 1;
}

/* CONCEPT
S → id = E
E → E+T
E → T
T → id
T → number
*/
