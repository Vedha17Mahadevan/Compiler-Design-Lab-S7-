/*Design and implement a three-address code generator and perform machine independent
optimization.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct TAC {
	char result[20];
	char arg1[20];
	char op;
	char arg2[20];
};

struct TAC code[100];
int tacCount = 0;
int tempCount = 1;
char stack[100];
int top = -1;

void push(char c) {
	stack[++top] = c;
}

char pop() {
	return stack[top--];
}

int precedence(char c) { 
	if(c == '+' || c == '-') {
		return 1;
	}
	if(c == '/' || c == '*') {
		return 2;
	}
	return 0;
}

void infixToPostfix(char infix[],char postfix[]) {
	int j = 0;
	top = -1;
	char c;
	for(int i = 0;infix[i] != '\0';i++) {
		c = infix[i];
		if(isalnum(c)) {
			postfix[j++] = c;
		}
		else if(c == '(') {
			push(c);
		}
		else if(c == ')') {
			while(top != -1 && stack[top] != '(') {
				postfix[j++] = pop();
			}
			pop();
		}
		else if(c == '+' || c == '-' || c == '*' || c == '/') {
			while(top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) {
				postfix[j++] = pop();
			}
			push(c);
		}
	}
	while(top != -1) {
		postfix[j++] = pop();
	}
	postfix[j] = '\0';
}

void generateTAC(char postfix[],char lhs) {
  char operandStack[100][20];
  int top2 = -1;
  char op1[20],op2[20],temp[20];
  int i;
  tacCount = 0;
  tempCount = 1;
  
  for(int i = 0;postfix[i] != '\0';i++) {
    char c = postfix[i];
    if(isalnum(c)) {
      operandStack[++top2][0] = c;
      operandStack[top2][1] = '\0';
    }
    else{
    	strcpy(op2,operandStack[top2--]);
    	strcpy(op1,operandStack[top2--]);
    	sprintf(temp,"t%d",tempCount++);
    	strcpy(code[tacCount].result,temp);
    	strcpy(code[tacCount].arg1,op1);
    	code[tacCount].op = c;
    	strcpy(code[tacCount].arg2,op2);
    	tacCount++;
    	strcpy(operandStack[++top2],temp);
    }
  }
  strcpy(code[tacCount].result,"");
  strcpy(code[tacCount].arg1,operandStack[top2]);
  code[tacCount].op = '=';
  strcpy(code[tacCount].arg2,"");
  tacCount++;
  code[tacCount - 1].result[0] = lhs;
  code[tacCount - 1].result[1] = '\0';
}

void displayTAC() {
	for(int i = 0;i < tacCount;i++) {
		if(code[i].op == '=') {
			printf("%s = %s\n",code[i].result,code[i].arg1);
		}
		else {
			printf("%s = %s %c %s\n",code[i].result,code[i].arg1,code[i].op,code[i].arg2);
		}
	}
}

int isNumber(char str[]) {
	for(int i = 0;str[i] != '\0';i++) {
		if(!isdigit(str[i])) {
			return 0;
		}
	}	
	return 1;
}

void constantFolding() {
	int a,b,result;
	for(int i = 0;i < tacCount;i++) {
		if(code[i].op != '=' && isNumber(code[i].arg1) && isNumber(code[i].arg2)) {
			a = atoi(code[i].arg1);
			b = atoi(code[i].arg2);
			switch(code[i].op){
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					if(b == 0) {
						continue;
					}
					result = a / b;
					break;
				default:
					continue;
			}
			sprintf(code[i].arg1,"%d",result);
			code[i].op = '=';
			strcpy(code[i].arg2,"");
		}
	}
}

void copyPropagation() {
	for(int i = 0;i < tacCount;i++) {
		if(code[i].op == '=' && !isNumber(code[i].arg1) && strcmp(code[i].result,code[i].arg1) != 0) {
			char var[20];
			strcpy(var,code[i].result);
			for(int j = i + 1;j < tacCount;j++) {
				if(strcmp(code[j].arg1,var) == 0) {
					strcpy(code[j].arg1,code[i].arg1);
				}
				if(strcmp(code[j].arg2,var) == 0){
					strcpy(code[j].arg2,code[i].arg1);
				}
			}
		}
	}
} 

void commonSubexpression() {
	for(int i = 0;i < tacCount;i++) {
		if(code[i].op == '=') {
			continue;
		}
		for(int j = 0;j < i;j++) {
			if(code[j].op == code[i].op && strcmp(code[j].arg1,code[i].arg1) == 0 && strcmp(code[j].arg2,code[i].arg2) == 0) {
				code[i].op = '=';
				strcpy(code[i].arg1,code[j].result);
				strcpy(code[i].arg2,"");
				break;
			}
		}
	}
}

void deadCodeElimination() {
	int used,changed,j,i;
	do{
		changed = 0;
		for(i = 0;i < tacCount;i++) {
			if(code[i].result[0] == 't') {
				used = 0;
				for(j = 0;j < tacCount;j++){
					if(strcmp(code[j].arg1,code[i].result) == 0 || strcmp(code[j].arg2,code[i].result) == 0) {
					used = 1;
					break;
					}
				}
				if(used == 0) {
					for(j = i;j < tacCount - 1;j++) {
						code[j] = code[j + 1];
					}
					tacCount--;
					changed = 1;
					break;
				}
			}
		}
	}while(changed);
}

void main() {
	char input[100];
	char infix[100];
	char postfix[100];
	char lhs;
	
	printf("Enter the expression:");
	scanf("%s",input);
	lhs = input[0];
	
	strcpy(infix,strchr(input,'=') + 1);
	infixToPostfix(infix,postfix);
	generateTAC(postfix,lhs);
	
	printf("\nThree Address Code\n");
	
	displayTAC();
	
	constantFolding();
	
	commonSubexpression();
	
	copyPropagation();
	
	deadCodeElimination();
	
	printf("\nOptimized Three Address Code\n");
	displayTAC();
	
}

/*OUTPUT
Enter the expression:a=(b*c)+(b*c)

Three Address Code
t1 = b * c
t2 = b * c
t3 = t1 + t2
a = t3

Optimized Three Address Code
t1 = b * c
t3 = t1 + t1
a = t3

Enter the expression:a=b+c

Three Address Code
t1 = b + c
a = t1

Optimized Three Address Code
t1 = b + c
a = t1

*/
