// Infix to Postfix Conversion and Evaluator

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Stack Functions Prototypes:
void push(char ch);
char pop();
char peek();
int isEmpty();

// Converter / Evaluator Function Prototypes:
void readInfix(char infix[]);
int precedence(char op);
void infixToPostfix(char infix[], char postfix[]);
int evaluate(char postfix[]);

int main(void) {
    
	char infix[100], postfix[100];
	
	int choice;
	
	printf("Infix to Postfix Converter + Postfix Evaluator:\n");
	while (true) {
		printf("------------------------------------------------\n");
		printf("1. Enter infix expression\n");
		printf("2. Convert infix to postfix expression\n");
		printf("3. Display postfix expression\n");
		printf("4. Postfix Evaluator\n");
		printf("5. Exit\n");
		printf("------------------------------------------------\n");
		printf("Enter your choice (1/2/3/4/5): ");
		scanf("%d", &choice);
		printf("------------------------------------------------\n");
		switch (choice) {
			case 1:
				readInfix(infix);
				break;
			case 2: 
				infixToPostfix(infix, postfix);
				break;
			case 3:
				printf("Postfix: %s\n", postfix);
				break;
			case 4:
				printf("Result: %d\n", evaluate(postfix));
				break;
			case 5:
				return 0;
				break;
			default:
				printf("Invalid input, please enter numbers from 1-5 ONLY!\n");
		}
	}
}

// Stack Functions:
void push(char ch) {
	if (top == MAX - 1) {
		printf("Stack Overflow\n");
		return;
	}
	stack[++top] = ch;
}

char pop() {
	if (top == -1) {
		return '\0';
	} return stack[top--];
}

char peek() {
	if (top == -1)
		return '\0';
	return stack[top];
}

int isEmpty() {
	return top == -1;
}

// Precedence Function:
int precedence(char op) {
	switch(op) {
		case '^': return 3;
		case '*': case '/': return 2;
		case '+': case '-': return 1;
		default: return 0;
	}
}
			
// Read Infix Expression:
void readInfix(char infix[]) {
	printf("Enter infix expression: ");
	scanf("%s", infix);
}

// Infix to Postfix Function:
void infixToPostfix(char infix[], char postfix[]) {
	int i = 0, j = 0;
	char ch;
	
	while ((ch = infix[i]) != '\0') {
		if (isalnum(ch)) {
			postfix[j++] = ch;
		}
		
		else if (ch == '(') {
			push(ch);
		}
		
		else if (ch == ')') {
			while (!isEmpty() && peek() != '(') {
				postfix[j++] = pop();
			} pop();
		}
		
		else {
			while (!isEmpty() && 
				((precedence(peek()) > precedence(ch)) 
				|| (precedence(peek()) == precedence(ch) && ch != '^')) && peek() != '(') {
				postfix[j++] = pop();
			} push(ch);
		}
		
		i++;
	}
	
	while (!isEmpty()) {
		postfix[j++] = pop();
	} postfix[j] = '\0';
	
	printf("Expression converted successfully!\n");
}

int evaluate(char postfix[]) {
	int values[26] = {0};
	int entered[26] = {0};
	
	int i = 0;
	
	while (postfix[i] != '\0') {
		if (isalpha(postfix[i])) {
			int index = toupper(postfix[i]) - 'A';
			
			if (!entered[index]) {
				printf("Enter value of %c: ", postfix[i]);
				scanf("%d", &values[index]);
				entered[index] = 1;
			}
			
			push(values[index]);
		}
		
		else {
			int b = pop();
			int a = pop();
			
			switch (postfix[i]) {
				case '+':
					push(a+b);
					break;
				case '-':
					push(a-b);
					break;
				case '*':
					push(a*b);
					break;
				case '/':
					push(a/b);
					break;
				case '^':
					push((int) pow(a,b));
					break;
			}
		}
		i++;
	}
	return pop();
}
