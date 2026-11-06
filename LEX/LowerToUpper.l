/*---------------------------------------------------------
 Program:
  Design and implement a Lex program to convert all
  lowercase letters in the input text to uppercase,
  while leaving all other characters unchanged.
----------------------------------------------------------*/

/* File Name : lowercase_to_uppercase.l */

%{
#include <stdio.h>
#include <ctype.h>
%}

/*-------------------- Rules Section --------------------*/
%%

/* Convert lowercase letters to uppercase */
[a-z]
{
    printf("%c", toupper(yytext[0]));
}

/* Print all other characters as they are */
.
{
    printf("%s", yytext);
}

%%

/*-------------------- User Code Section --------------------*/

int main()
{
    printf("Enter text:\n");
    yylex();
    return 0;
}

/* Indicates end of input */
int yywrap()
{
    return 1;
}
