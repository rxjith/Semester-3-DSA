#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

char stack[MAX];
int top = -1;

char infix[MAX], postfix[MAX];
Node* root = NULL;


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

Node* treeStack[MAX];
int treeTop = -1;

void pushTree(Node* ptr) {
    if (treeTop == MAX - 1) {
        printf("Tree Stack overflow!\n"); return;
    }
    treeStack[++treeTop] = ptr;
}

Node* popTree(void) {
    if (treeTop == -1) {
        printf("Tree Stack underflow!\n"); return NULL;
    }
    return treeStack[treeTop--];
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
        } else {
            while (!isEmpty() && ((precedence(peek()) >= precedence(ch)) || (precedence(peek()) == precedence(ch) && ch != '^')) && peek() != '(') {
                postfix[j++] = pop();
            } push(ch);
        }
        i++;
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    } postfix[j] = '\0';
}

void buildExpressionTree(void) {
    treeTop = -1;
    int i = 0; char ch;

    while ((ch = postfix[i]) != '\0') {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = ch;
        newNode->left = NULL;
        newNode->right = NULL;

        if (isalnum(ch)) {
            pushTree(newNode);
        } else {
            newNode->right = popTree();
            newNode->left = popTree();
            pushTree(newNode);
        }
        i++;
    }
    root = popTree();
}

void preOrder(Node* ptr) {
    if (ptr != NULL) {
        printf("%c", ptr->data);
        preOrder(ptr->left);
        preOrder(ptr->right);
    }
}

void postOrder(Node* ptr) {
    if (ptr != NULL) {
        postOrder(ptr->left);
        postOrder(ptr->right);
        printf("%c", ptr->data);
    }
}

void freeTree(Node* ptr) {
    if (ptr != NULL) {
        freeTree(ptr->left);
        freeTree(ptr->right);
        free(ptr);
    }
}

int main(void) {
    int choice;
    
    printf("Infix Expression Tree & Traversals Program\n");

    while (1) {
        printf("----------------------------------------------------\n");
        printf("1. Read infix expression\n");
        printf("2. Convert to Expression Tree\n");
        printf("3. Display Prefix Expression (Pre-order Traversal)\n");
        printf("4. Display Postfix Expression (Post-order Traversal)\n");
        printf("5. Exit\n");
        printf("----------------------------------------------------\n");
        printf("Enter your choice (1-5): "); scanf("%d", &choice);
        printf("----------------------------------------------------\n");

        switch (choice) {
            case 1:
                readInfix();
                break;
            case 2:
                convertInfixToPostfix();
                freeTree(root);
                root = NULL;
                buildExpressionTree();
                printf("Expression Tree constructed successfully from postfix!\n");
                break;
            case 3:
                if (root == NULL) {
                    printf("Expression tree not built yet! Please run option 2 first.\n");
                } else {
                    printf("Prefix expression: ");
                    preOrder(root);
                    printf("\n");
                }
                break;
            case 4:
                if (root == NULL) {
                    printf("Expression tree not built yet! Please run option 2 first.\n");
                } else {
                    printf("Postfix expression: ");
                    postOrder(root);
                    printf("\n");
                }
                break;
            case 5:
                printf("Freeing memory and exiting program...\n");
                freeTree(root);
                root = NULL;
                exit(0);
            default:
                printf("Invalid choice, please enter a choice from 1-5 only!\n");
        }
    }
}