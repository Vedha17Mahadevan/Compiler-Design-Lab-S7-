/*Implement a C program for a Non deterministic finite automaton which verifies e-mail
id and password. Alphabet can be : {A-Z|a-z| . | @| $ | *}
Rules for a valid e-mail id:
(i) Mail id should start with first name followed by ‘.’ and last name.
(ii) The domain name should be xyz and domain extension can be ‘.in’ or ‘.com’.
Rules for password:
(i) The password should have at least 6 characters which include digits and english
alphabets, special characters like @, $, and *.
(ii) The password should start with a digit or english alphabet.
(iii) It should have at least one special character, such as @, $, or *.
Expected Output:
a. Accept the input from console
b. Verifies the e-mail id and password with all possible ways and display.
c. Find how many backtracking needed.
d. If not accepted, display the violating conditions.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int backtrack = 0;

// Email validation
int validateEmail(char email[])
{
    int i = 0;

    // First name
    if(!(isalpha(email[i])))
    {
        printf("Violation: First name must start with a letter.\n");
        return 0;
    }

    while(isalpha(email[i]))
        i++;

    if(email[i] != '.')
    {
        printf("Violation: Missing '.' between first and last name.\n");
        return 0;
    }

    i++;

    // Last name
    if(!(isalpha(email[i])))
    {
        printf("Violation: Last name missing.\n");
        return 0;
    }

    while(isalpha(email[i]))
        i++;

    if(email[i] != '@')
    {
        printf("Violation: Missing '@'.\n");
        return 0;
    }

    i++;

    // Domain name
    if(strncmp(&email[i], "xyz", 3) != 0)
    {
        printf("Violation: Domain name must be xyz.\n");
        return 0;
    }

    i += 3;

    if(strcmp(&email[i], ".com") == 0)
        return 1;

    if(strcmp(&email[i], ".in") == 0)
        return 1;

    printf("Violation: Domain extension must be .com or .in\n");
    return 0;
}

// Password validation
int validatePassword(char pass[])
{
    int len = strlen(pass);

    if(len < 6)
    {
        printf("Violation: Password should contain at least 6 characters.\n");
        return 0;
    }

    if(!(isalnum(pass[0])))
    {
        printf("Violation: Password should start with a letter or digit.\n");
        return 0;
    }

    int letter = 0;
    int digit = 0;
    int special = 0;

    for(int i=0;i<len;i++)
    {
        if(isalpha(pass[i]))
            letter = 1;

        else if(isdigit(pass[i]))
            digit = 1;

        else if(pass[i]=='@' || pass[i]=='$' || pass[i]=='*')
            special = 1;

        else
        {
            backtrack++;
            printf("Violation: Invalid character '%c'\n",pass[i]);
            return 0;
        }
    }

    if(!letter)
    {
        printf("Violation: Password should contain alphabets.\n");
        return 0;
    }

    if(!digit)
    {
        printf("Violation: Password should contain digits.\n");
        return 0;
    }

    if(!special)
    {
        printf("Violation: Password should contain @, $ or *.\n");
        return 0;
    }

    return 1;
}

int main()
{
    char email[100], password[100];

    printf("Enter Email ID : ");
    scanf("%s",email);

    printf("Enter Password : ");
    scanf("%s",password);

    printf("\nEMAIL VERIFICATION\n");

    if(validateEmail(email))
        printf("Valid Email ID\n");
    else
    {
        backtrack++;
        printf("Invalid Email ID\n");
    }

    printf("\nPASSWORD VERIFICATION\n");

    if(validatePassword(password))
        printf("Valid Password\n");
    else
    {
        backtrack++;
        printf("Invalid Password\n");
    }

    printf("\nTotal Backtracking Needed : %d\n",backtrack);

    return 0;
}
