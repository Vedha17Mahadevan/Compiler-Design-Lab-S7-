//Three Address Code Generation with Common Subexpression Elimination
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct TAC
{
    char result[20];
    char arg1[20];
    char op;
    char arg2[20];
};

struct TAC code[MAX];

int tacCount = 0;
int tempCount = 1;

char stack[MAX];
int top = -1;

//-------------------- Stack Functions --------------------

void push(char c)
{
    stack[++top] = c;
}

char pop()
{
    return stack[top--];
}

//-------------------- Precedence --------------------

int precedence(char c)
{
    if(c=='+' || c=='-')
        return 1;

    if(c=='*' || c=='/')
        return 2;

    return 0;
}

//-------------------- Infix to Postfix --------------------

void infixToPostfix(char infix[], char postfix[])
{
    int j = 0;
    top = -1;

    for(int i=0; infix[i]!='\0'; i++)
    {
        char c = infix[i];

        if(isalnum(c))
        {
            postfix[j++] = c;
        }

        else if(c=='(')
        {
            push(c);
        }

        else if(c==')')
        {
            while(top!=-1 && stack[top]!='(')
                postfix[j++] = pop();

            pop();
        }

        else if(c=='+' || c=='-' || c=='*' || c=='/')
        {
            while(top!=-1 &&
                  stack[top]!='(' &&
                  precedence(stack[top])>=precedence(c))
            {
                postfix[j++] = pop();
            }

            push(c);
        }
    }

    while(top!=-1)
        postfix[j++] = pop();

    postfix[j]='\0';
}

//-------------------- Generate TAC --------------------

void generateTAC(char postfix[], char lhs)
{
    char operandStack[MAX][20];
    int top2 = -1;

    tacCount = 0;
    tempCount = 1;

    for(int i=0; postfix[i]!='\0'; i++)
    {
        char c = postfix[i];

        if(isalnum(c))
        {
            operandStack[++top2][0] = c;
            operandStack[top2][1] = '\0';
        }

        else
        {
            char op1[20], op2[20], temp[20];

            strcpy(op2, operandStack[top2--]);
            strcpy(op1, operandStack[top2--]);

            sprintf(temp,"t%d",tempCount++);

            strcpy(code[tacCount].result,temp);
            strcpy(code[tacCount].arg1,op1);
            strcpy(code[tacCount].arg2,op2);
            code[tacCount].op=c;

            strcpy(operandStack[++top2],temp);

            tacCount++;
        }
    }

    strcpy(code[tacCount].result,"");
    strcpy(code[tacCount].arg1,operandStack[top2]);
    strcpy(code[tacCount].arg2,"");
    code[tacCount].op='=';

    tacCount++;

    code[tacCount-1].result[0]=lhs;
    code[tacCount-1].result[1]='\0';
}

//-------------------- Display TAC --------------------

void displayTAC()
{
    for(int i=0;i<tacCount;i++)
    {
        if(code[i].op=='=')
            printf("%s = %s\n", code[i].result, code[i].arg1);

        else
            printf("%s = %s %c %s\n",code[i].result, code[i].arg1, code[i].op, code[i].arg2);
    }
}

//-------------------- Common Subexpression --------------------

void commonSubexpression()
{
    for(int i=0;i<tacCount;i++)
    {
        if(code[i].op=='=')
            continue;

        for(int j=0;j<i;j++)
        {
            if(code[j].op==code[i].op &&
               strcmp(code[j].arg1,code[i].arg1)==0 &&
               strcmp(code[j].arg2,code[i].arg2)==0)
            {
                code[i].op='=';
                strcpy(code[i].arg1,code[j].result);
                strcpy(code[i].arg2,"");
                break;
            }
        }
    }
}

//-------------------- Quadruples --------------------

void displayQuadruple()
{
    printf("\nQuadruples\n");
    printf("---------------------------------------------\n");
    printf("Op\tArg1\tArg2\tResult\n");
    printf("---------------------------------------------\n");

    for(int i=0;i<tacCount;i++)
    {
        printf("%c\t%s\t%s\t%s\n",
               code[i].op,
               code[i].arg1,
               code[i].arg2,
               code[i].result);
    }
}

//-------------------- Main --------------------

int main()
{
    char input[100];
    char infix[100];
    char postfix[100];
    char lhs;

    printf("Enter expression : ");
    scanf("%s",input);

    lhs = input[0];

    strcpy(infix, strchr(input,'=')+1);

    infixToPostfix(infix,postfix);

    generateTAC(postfix,lhs);

    printf("\nThree Address Code\n");
    displayTAC();

    commonSubexpression();

    printf("\nAfter Common Subexpression Elimination\n");
    displayTAC();

    displayQuadruple();

    printf("\nMinimum Temporary Variables Used : %d\n",
           tempCount-1);

    return 0;
}
