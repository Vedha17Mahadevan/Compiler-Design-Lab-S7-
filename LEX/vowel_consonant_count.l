/*---------------------------------------------------------
Program:
  Design and implement a Lex program to count the number of
  vowels and consonants present in the input text.
----------------------------------------------------------*/

%{
#include <stdio.h>

/* Global counters */
int vowels = 0;
int consonants = 0;
%}

/*-------------------- Rules Section --------------------*/
%%

/* Match vowels (both uppercase and lowercase) */
[AaEeIiOoUu]            { vowels++; }

/* Match consonants (both uppercase and lowercase) */
[B-DF-HJ-NP-TV-Zb-df-hj-np-tv-z]
                        { consonants++; }

/* Ignore all other characters (digits, spaces, symbols, etc.) */
.                       ;

%%

/*-------------------- User Code Section --------------------*/

int main()
{
    printf("Enter text:\n\n");

    yylex();

    printf("\n--------- Output ---------\n");
    printf("Vowels      : %d\n", vowels);
    printf("Consonants  : %d\n", consonants);

    return 0;
}

/* Indicates end of input */
int yywrap()
{
    return 1;
}