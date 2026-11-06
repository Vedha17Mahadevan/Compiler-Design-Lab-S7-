//SR Parser with Conflict Counter
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char lhs[MAX], rhs[MAX][MAX];
char stack[MAX];
int n, top = -1;

int shiftReduceConflict = 0;
int reduceReduceConflict = 0;

void removeSpaces(char *s)
{
    int j = 0;
    for(int i=0; s[i]; i++)
    {
        if(!isspace((unsigned char)s[i]))
            s[j++] = s[i];
    }
    s[j]='\0';
}

int canReduce(int p,char next)
{
    char *r = rhs[p];
    int len = strlen(r);

    if(top+1 < len)
        return 0;

    for(int i=0;i<len;i++)
    {
        if(stack[top-len+1+i] != r[i])
            return 0;
    }

    /* precedence handling */

    if(p==1 && next=='*')
        return 0;

    if(p==3 && next=='+')
        return 1;

    if(p==4)
        return 1;

    if(p==2)
    {
        if(next=='*')
            return 0;
        return 1;
    }

    if(p==0)
    {
        if(next=='*' || next=='+')
            return 0;
        return 1;
    }

    return 1;
}

int findReduction(char next)
{
    int found = -1;

    for(int i=0;i<n;i++)
    {
        if(canReduce(i,next))
        {
            if(found==-1)
                found=i;
            else
                reduceReduceConflict++;
        }
    }

    return found;
}

void displayStack()
{
    for(int i=0;i<=top;i++)
        printf("%c",stack[i]);
}

int main()
{
    printf("Enter number of productions : ");
    scanf("%d",&n);
    getchar();

    printf("\nEnter productions\n");

    for(int i=0;i<n;i++)
    {
        char line[MAX];

        printf("Production %d : ",i+1);

        fgets(line,sizeof(line),stdin);

        line[strcspn(line,"\n")]='\0';

        removeSpaces(line);

        char *arrow = strstr(line,"->");

        if(arrow==NULL)
        {
            printf("Invalid Production\n");
            return 0;
        }

        lhs[i]=line[0];

        strcpy(rhs[i],arrow+2);
    }

    char input[MAX];

    printf("\nEnter input string : ");
    scanf("%s",input);

    int inputLen=strlen(input);

    input[inputLen]='$';
    input[inputLen+1]='\0';
    inputLen++;

    stack[++top]='$';

    int pos=0;
    int step=1;

    printf("\nParsing Steps\n\n");

    printf("%-5s %-15s %-15s %-20s\n",
           "Step","Stack","Input","Action");

    printf("-------------------------------------------------------------\n");

    while(1)
    {
        printf("%-5d",step++);

        displayStack();

        printf("%*s",15-(top+1),"");

        printf("%-15s",&input[pos]);

        if(pos==inputLen-1 &&
           top==1 &&
           stack[1]==lhs[0])
        {
            printf("ACCEPT\n");
            break;
        }

        char next=input[pos];

        int r=findReduction(next);

        if(r!=-1)
        {
            int len=strlen(rhs[r]);

            printf("Reduce %c->%s  (Handle=%s)\n",
                   lhs[r],rhs[r],rhs[r]);

            top-=len;

            stack[++top]=lhs[r];

            continue;
        }

        if(pos<inputLen)
        {
            shiftReduceConflict++;

            stack[++top]=input[pos];

            printf("Shift %c\n",stack[top]);

            pos++;
        }
        else
        {
            printf("ERROR\n");
            break;
        }
    }

    printf("\n----------------------------------\n");
    printf("Shift-Reduce Operations : %d\n",shiftReduceConflict);
    printf("Reduce-Reduce Conflicts : %d\n",reduceReduceConflict);
    printf("----------------------------------\n");

    return 0;
}
