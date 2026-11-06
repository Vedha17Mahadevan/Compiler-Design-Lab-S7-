//lex.l
%{
#include "y.tab.h"
%}

%%
[a-z]+      { return STRING; }
\n          { return '\n'; }
[ \t]       ;
%%

int yywrap()
{
    return 1;
}

//parser.y
%{
#include<stdio.h>
#include<string.h>

char input[100];

int yylex();
void yyerror(char *s);
%}

%token STRING

%%

start :
      STRING '\n'
      {
          int i,j;
          printf("Enter String : ");
      }
      ;

%%

int main()
{
    scanf("%s",input);

    int i=0,j=strlen(input)-1;

    while(i<j)
    {
        if(input[i]!=input[j])
        {
            printf("Not Palindrome\n");
            return 0;
        }
        i++;
        j--;
    }

    printf("Palindrome\n");
    return 0;
}

void yyerror(char *s)
{
}
