/*---------------------------------------------------------
Program:
  Design and implement a Lex program to recognize and
  classify different types of operators in C.

  The program identifies the following categories:
  • Relational Operators
  • Arithmetic and Assignment Operators
  • Logical Operators
  • Bitwise Operators
----------------------------------------------------------*/

/* File Name : operator_recognition.l */

%{
#include <stdio.h>
%}

/*-------------------- Rules Section --------------------*/
%%

/* Relational Operators */
"=="|"!="|">="|"<="|">"|"<"
{
    printf("%s -> Relational Operator\n", yytext);
}

/* Arithmetic and Assignment Operators */
"+"|"-"|"*"|"/"|"%"|"="
{
    printf("%s -> Arithmetic/Assignment Operator\n", yytext);
}

/* Logical Operators */
"&&"|"||"|"!"
{
    printf("%s -> Logical Operator\n", yytext);
}

/* Bitwise Operators */
"&"|"|"|"^"|"<<"|">>"
{
    printf("%s -> Bitwise Operator\n", yytext);
}

/* Ignore all other characters */
.|\n ;

%%

/*-------------------- User Code Section --------------------*/

int main()
{
    printf("Enter operators:\n");
    yylex();
    return 0;
}

/* Indicates end of input */
int yywrap()
{
    return 1;
}