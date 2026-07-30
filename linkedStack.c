#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *top = NULL;

void push(int value);
int pop(void);
int peek(void);
void display(void);
void freeStack(void);

int main(void) {
    int choice, value, item;
    printf("Linked List representation of Stack:\n");
    
    while (true) {
        printf("------------------------------------\n");
        printf("1. Push to Stack\n2. Pop from Stack\n3. Peek at top\n4. Display Stack\n5. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &value);
                push(value);
                break;

            case 2:
                item = pop();
                if (item != -1) {
                    printf("Popped item: %d\n", item);
                }
                break;

            case 3:
                item = peek();
                if (item != -1) {
                    printf("Item at the top of stack: %d\n", item);
                }
                break;

            case 4:
                display();
                break;

            case 5:
                freeStack();
                printf("Memory freed! Exiting program...\n");
                return 0;

            default:
                printf("Invalid input, please try again!\n");
                break;
        }
    }
    return 0;
}

void push(int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed (Stack Overflow)!\n");
        return;
    }

    newNode->data = value;
    newNode->next = top;
    top = newNode;
    printf("Successfully pushed %d\n", value);
}

int pop(void) {
    if (top == NULL) {
        printf("Stack Underflow!\n");
        return -1;
    }

    Node *temp = top;
    int item = temp->data;
    top = top->next;
    free(temp);
    return item;
}

int peek(void) {
    if (top == NULL) {
        printf("Stack Underflow, nothing to see here!\n");
        return -1;
    }

    return top->data;
}

void display(void) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }

    Node *temp = top;
    printf("Top\n | \n v \n");
    while (temp != NULL) {
        printf("[%d]\n | \n v \n", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeStack(void) {
    Node *temp = top;
    Node *nextNode;

    while (temp != NULL) {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    top = NULL;
}