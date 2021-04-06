#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

typedef enum{
    FALSE, TRUE
}BOOLEAN;

//*****Implementation of stack for the operators********//
typedef struct{
    char item[SIZE];
    int top;
}OprStack;

// function declaration
void opr_push(OprStack *, char);
char opr_pop(OprStack *);

void opr_push(OprStack *sp, char value){
	if (sp->top == SIZE - 1){
		printf("Stack Overflow\n");
		return;
	}

	//top++;
	sp->item[++sp->top] = value;
} 

char opr_pop(OprStack *sp){
	if (sp->top == -1){
		printf("Stack Underflow\n");
		return '\0';
	}
	int value = sp->item[sp->top--];
	return value;
}

//***********End of stack implementation for operators******************//

/**
	prcd (op, '(' ) = FALSE
	prcd ('(', op ) = FALSE,
	prcd(op, ')') = TRUE,  except op = '('
	prcd('(', ')') = FALSE, we should push, however instead of PUSH we will pop
	prcd('/', '')
*/
BOOLEAN prcd(char left, char right){
	if (left == '(' || right == '(')
		return FALSE;
	if (right == ')')
		return TRUE;

	if (left == '*' || left == '/'){
		if (right == '*' ||  right == '/' || right == '+' || right == '-')
			return TRUE;
		else 
			return FALSE;
	}
	if (left == '+' || left == '-'){
		if (right == '+' || right == '-')
			return TRUE;
		else 
			return FALSE;
	}
	if (left == '$'){
		return TRUE;
	}
	else 
		return FALSE;
}

/* 
   conversion: converts the supplied infix string to postfix string and assigns that 
   postfix string to the postfix array supplied as parameter

*/
void convert(char infix[], char postfix[]){
    OprStack stack;
    stack.top = -1;
    int i = 0, j = 0;
    while(infix[i] != '\0'){
        char next = infix[i];
        // if the token is an operand
        if(next >= '0' && next <='9'){
            postfix[j++] = infix[i];
        }
        // if the token is an operator
        else if(next == '+' || next == '-' || next =='/' || next == '*' || next == '$' || next == '(' || next ==')'){
            while(stack.top!=-1 && prcd(stack.item[stack.top], next)){
                postfix[j++] = opr_pop(&stack);
            }
			if (next == ')')
                opr_pop(&stack);
			else
				opr_push(&stack, next);
		}
		else{
			printf("Invalid symbol %c encountered, terminating the program\n", next);
			exit(0);       
        }
        i++;
    }
    while(stack.top != -1){
		postfix[j++] = opr_pop(&stack);
	}
	postfix[j] = '\0';
}

int main(int argc, char const *argv[])
{
	char postfix[SIZE], infix[SIZE];
	printf("Input infix string: ");
	
	scanf("%s", infix);
	convert(infix, postfix);
	printf("Postfix string: %s\n", postfix);
	return 0;
}
