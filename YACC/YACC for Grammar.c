/* SAMPLE INPUT 
S → aSb
S → ab
*/

//lex.l
%{
#include "y.tab.h"
%}

%%
a       { return 'a'; }
b       { return 'b'; }
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
      'a' S 'b'
    | 'a' 'b'
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
