/*
Design and implement a lexical analyzer that recognizes the following C language tokens:
● Keywords: if, int, else, main, printf, scanf.
● Identifiers: Valid identifiers satisfying the specifications given in Question 2.
● Relational Operators: <, >, <=, >=, =, ==,<>
● Arithmetic Operators: +, ++, -, --
● Delimiters: , and ;
a. Take input from a file having a simple C program.
b. Print the input
c. Print output token of the form <token name, attribute value>
d. Display the symbol table
*/

//CODE -> e1.c
#include <stdio.h>

#define MAXTOK 100
#define MAXLEN 50

char symbT[MAXTOK][MAXLEN];
int symbolCount=0;

int equal(char a[],char b[])
{
  int i=0;
  while(a[i]!='\0' && b[i]!='\0')
  {
   if(a[i]!=b[i])
      return 0;
   i++;
  }
  if(a[i]=='\0' && b[i]=='\0')
       return 1;
  return 0;
}

void strCpy(char dest[],char src[])
{
  int i=0;
  while(src[i]!='\0')
  {
     dest[i]=src[i];
     i++;
  }
  dest[i]='\0';
}

int isKeyword(char ch[])
{
   if(ch[0]=='i' && ch[1]=='n' && ch[2]=='t' && ch[3]=='\0')
     return 1;
   if(ch[0]=='i' && ch[1]=='f' && ch[2]=='\0')
     return 1;
   if(ch[0]=='e' && ch[1]=='l' && ch[2]=='s' && ch[3]=='e' && ch[4] =='\0')
     return 1;
   if(ch[0]=='v' && ch[1]=='o' && ch[2]=='i' && ch[3]=='d' && ch[4] =='\0')
     return 1;
   if(ch[0]=='m' && ch[1]=='a' && ch[2]=='i' && ch[3]=='n' && ch[4] =='\0')
     return 1;
  if(ch[0]=='p' && ch[1]=='r' && ch[2]=='i' && ch[3]=='n' && ch[4] =='t' &&  ch[4] =='f' && ch[5] =='\0')
     return 1;
 return 0;
}

int isIdentifier(char ch[])
{
  int i;
  if(!(ch[0]>='a' && ch[0]<='z'))
     return 0;
  i=1;
  while(ch[i]!='\0')
  {
      if(!((ch[i]>='a' && ch[i]<='z') || (ch[i]>='0' && ch[i]<='9')))
         return 0;
      i++;
  }
  return 1;
}

int isDig(char ch[])
{
  int i=0;
  int dot=0;
  while(ch[i]!='\0')
  {
    if(ch[i]=='.')
    {
      dot++;
      if(dot>1)
       return 0;
    }
    else if(!(ch[i]>='0' && ch[i]<='9'))
      return 0;
    i++;
}
return 1;
}

void addsymbol(char token[])
{
  int i;
  for(i=0; i<symbolCount;i++)
  {
    if(equal(symbT[i],token))
       return;
  }
  strCpy(symbT[symbolCount],token);
  symbolCount++;
}
   
int main()
{
  FILE *fp=fopen("input.txt","r");
  char ch;
  char token[100];
  int i=0;
  int j;
  
  if(fp==NULL){
    printf("Cannot Open File");
    return 0;
  }
  
  printf("INPUT Program: \n\n");
  while((ch=fgetc(fp))!=EOF)
    putchar(ch);
    
  rewind(fp);
  
  printf("\n\nTOKENS:\n");
  int sl=0;
  
  while((ch=fgetc(fp))!=EOF)
  {
    if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' && ch<='9') || ch=='.')
    {
      token[i]=ch;
      i++;
    }
    else
    {
        if(i>0)
        {
          token[i]='\0';
          if(isKeyword(token))
          {
            printf("%d. <%s, Keyword>\n",++sl,token);
          }
          else if(isIdentifier(token))
          {
            printf("%d. <%s, Identifier>\n",++sl, token);
            addsymbol(token);
          }
          else if(isDig(token))
          {
            printf("%d. <%s, Number>\n",++sl, token);
          }
          else
          {
            printf("%d. <%s, Invalid token>\n",++sl, token);
          }
          i=0;
      }
      if(ch==' '||ch=='\n'||ch=='\t')
        continue;
      if(ch=='<'|| ch=='>'|| ch=='=' || ch=='!')
      {
        char next=fgetc(fp);
        if(next=='=')
        {
          printf("%d. <%c%c, Relational operator>\n",++sl, ch,next);
        }
        else
        {
          printf("%d. <%c, Relational operator>\n",++sl, ch);
          if(next!=EOF)
            ungetc(next,fp);
        }
      }
      else if(ch==';' || ch==',' || ch=='(' || ch==')'|| ch=='[' || ch==']' || ch=='{' || ch =='}')
      {
        printf("%d. <%c, Delimeter>\n",++sl, ch);
      }
    }
  }
  if(i>0)
  {
    token[i]='\0';
    if(isKeyword(token))
    {
      printf("%d. <%s, Keyword>\n",++sl, token);
    }
    else if(isIdentifier(token))
    {
      printf("%d. <%s, Identifier>\n",++sl, token);
      addsymbol(token);
    }
    else if(isDig(token))
    {
      printf("%d. <%s, Number>\n",++sl, token);
    }
    else
    {
     printf("%d. <%s, Invalid token>\n",++sl, token);
    }
  }
  fclose(fp);

  printf("\n\nSYMBOL TABLE\n");
  printf("ID\tIdentifier\n");
  for(j=0;j<symbolCount;j++)
  {
    printf("id%d\t%s\n",j+1,symbT[j]);
  }
  return 0;
}
  
//input.txt
void main()
{
  int a=0, b=5, c=10;
  a = b+c;
  if(a>5)
    print(a)
  else
    print("nothing")
}

/* OUTPUT
INPUT Program: 

void main()
{
  int a=0, b=5, c=10;
  a = b+c;
  if(a>5)
    print(a)
  else
    print("nothing")
}


TOKENS:
1. <void, Keyword>
2. <main, Keyword>
3. <(, Delimeter>
4. <), Delimeter>
5. <{, Delimeter>
6. <int, Keyword>
7. <a, Identifier>
8. <=, Relational operator>
9. <0, Number>
10. <,, Delimeter>
11. <b, Identifier>
12. <=, Relational operator>
13. <5, Number>
14. <,, Delimeter>
15. <c, Identifier>
16. <=, Relational operator>
17. <10, Number>
18. <;, Delimeter>
19. <a, Identifier>
20. <=, Relational operator>
21. <b, Identifier>
22. <c, Identifier>
23. <;, Delimeter>
24. <if, Keyword>
25. <(, Delimeter>
26. <a, Identifier>
27. <>, Relational operator>
28. <5, Number>
29. <), Delimeter>
30. <print, Identifier>
31. <(, Delimeter>
32. <a, Identifier>
33. <), Delimeter>
34. <else, Keyword>
35. <print, Identifier>
36. <(, Delimeter>
37. <nothing, Identifier>
38. <), Delimeter>
39. <}, Delimeter>


SYMBOL TABLE
ID	Identifier
id1	a
id2	b
id3	c
id4	print
id5	nothing
*/