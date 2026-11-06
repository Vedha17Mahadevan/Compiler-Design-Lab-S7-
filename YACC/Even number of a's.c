//lex.l

%{
#include "y.tab.h"
%}

%%
a       { return 'a'; }
\n      { return '\n'; }
[ \t]   ;
%%

int yywrap()
{
    return 1;
}

//parser.y
%{
#include<stdio.h>

int yylex();
void yyerror(char *s);
%}

%%

S :
      'a' 'a' S
    |
    ;

%%

int main()
{
    printf("Enter String : ");
    yyparse();
    printf("Accepted\n");
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
