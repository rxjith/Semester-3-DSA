#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

char stack[MAX];
int top = -1;

void push(char ch);
char pop();
char peek();
int isEmpty();

int precedence(char op);

void readInfix(void);
void display(char []);
void convertInfixToPostfix(void);
void evaluatePostfix(void);

char infix[MAX], postfix[MAX];

int main(void) {
    
    int choice;
    
    printf("Infix to Postfix Converter + Evaluator Program\n");

    while (1) {
        printf("----------------------------------------------------\n");
        printf("1. Read infix expression\n2. Convert infix to postfix\n3. Evaluate postfix expression\n4. Exit\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice (1-4): "); scanf("%d", &choice);
        printf("----------------------------------------------------\n");

        switch (choice) {
            case 1:
                readInfix();
                break;
            case 2:
                convertInfixToPostfix();
                printf("Postfix expression: "); display(postfix);
                break;
            case 3:
                evaluatePostfix();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice, please enter a choice from 1-4 only!\n");
        }
    }
}

void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack overflow!\n"); return;
    } stack[++top] = ch;
}

char pop(void) {
    if (top == -1) {
        printf("Stack underflow!\n"); return '\0';
    } return stack[top--];
}

char peek(void) {
    if (top == -1) {
        printf("Stack underflow!\n"); return '\0';
    } return stack[top];
}

int isEmpty(void) {
    return top == -1;
}

int precedence(char op) {
	switch(op) {
		case '^': return 3;
		case '*': case '/': return 2;
		case '+': case '-': return 1;
		default: return 0;
	}
}

void readInfix(void) {
    printf("Enter infix expression: "); scanf(" %49[^\n]", infix);
    printf("----------------------------------------------------\n");
    printf("Infix expression: %s\n", infix);
    return;
}

void display(char expression[MAX]) {
    int i = 0; char ch;
    while ((ch = expression[i]) != '\0') {
        printf("%c", ch); i++;
    } printf("\n");
}

void convertInfixToPostfix() {

    top = -1;

    int i = 0, j = 0; char ch;

    while ((ch = infix[i]) != '\0') {
        if (isalnum(ch)) postfix[j++] = ch;

        else if (ch == '(') push(ch);

        else if (ch == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            } pop();
        }

        else {
            while (!isEmpty() && ((precedence(peek()) >= precedence(ch)) || (precedence(peek()) == precedence(ch) && ch != '^')) && peek() != '(') {
                postfix[j++] = pop();
            } push(ch);
        }

        i++;
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    } postfix[j] = '\0';

    printf("Expression Converted Successfully!\n");
}

void evaluatePostfix() {
    top = -1;

    int values[26] = {0};
    int entered[26] = {0};

    int i = 0; char ch;

    while ((ch = postfix[i]) != '\0') {
        if (isalpha(ch)) {
            int index = toupper(ch) - 'A';

            if (!entered[index]) {
                printf("Enter value of %c: ", ch); scanf("%d", &values[index]);
                entered[index] = 1;
            }

            push(values[index]);
        }

        else {
            int b = pop();
            int a = pop();

            switch (ch) {
                case '+': push(a+b); break;
                case '-': push(a-b); break;
                case '*': push(a*b); break;
                case '/': 
                    if (b == 0) {
                        printf("Error: Division by 0\n");
                        return;
                    }
                    push(a/b); break;
                case '^': push((int) pow(a, b)); break;
            }
        }

        i++;
    }
    printf("Evaluated Value: %d\n", pop());
}