#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isFull(int* , int);
bool isEmpty(int* );
int* createStack(int* size);
void push(int*, int* , int);
int pop(int*, int* );

int main(void) {
    
    printf("Stack Operations Demonstration Program");
    
    int choice, *stack = NULL, top = -1, size = 0;

    printf("%d", top); // DEBUG

    while (true) {
        printf("---------------------------------------------\n");
        printf("1. Create a stack\n");
        printf("2. Push\n");
        printf("3. Pop\n");
        printf("4. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter choice (1/2/3/4): ");
        scanf("%d", &choice);
        printf("---------------------------------------------\n");

        switch (choice) {
            case 1:
                if (stack != NULL) {
                    printf("Stack already exists!\n");
                } else {
                    stack = createStack(&size);
                }
                break;
            case 2:
                if (stack == NULL) {
                    printf("Please create a stack first!\n");
                } else {
                    push(stack, &top, size);
                }
                break;
            case 3:
                if (stack == NULL) {
                    printf("Please create a stack first!\n");
                } else if (!isEmpty(&top)) {
                    int poppedItem = pop(stack, &top);
                    int choice2;

                    printf("1. Print item\n");
                    printf("2. Delete item\n");
                    printf("---------------------------------------------\n");
                    printf("Enter your choice (1/2): ");
                    scanf("%d", &choice2);
                    printf("---------------------------------------------\n");

                    switch (choice2) {
                        case 1:
                            printf("Item: %d\n", poppedItem);
                            break;
                        case 2:
                            printf("Item has been deleted!\n");
                            break;
                        default:
                            printf("Invalid entry, item has been deleted!\n");
                    }
                }
                else {
                    printf("Stack Underflow! The stack is empty!\n");
                }
                break;
            case 4:
                free(stack);
                exit(0);
                break;
            default:
                printf("Invalid entry, please try again!\n");
        }

        free(stack);
        return 0;
    }
}

bool isFull(int* top, int size) {
    return (*top == size - 1);
}

bool isEmpty(int* top) {
    return (*top == -1);
}

int* createStack(int* size) {

    int n;
    printf("Enter # of member-spaces you want to allocate: ");
    scanf("%d", &n);
    printf("---------------------------------------------\n");
    int* newStack = (int*) malloc(n * sizeof(int));

    if (newStack == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    *size = n;
    printf("Stack memory allocated successfully!\n");
    return newStack;
}

void push(int* stack, int* top, int size) {

    if (isFull(top, size)) {
        printf("Stack Overflow! Cannot push item.\n");
        return;
    }

    int item;
    printf("Enter element to push into the stack: ");
    scanf("%d", &item);

    stack[++(*top)] = item;
    
    printf("---------------------------------------------\n");
    printf("%d pushed successfully!\n", item);
}

int pop(int* stack, int* top) {

    int item = stack[(*top)--];
    printf("Item popped successfully!\n");
    return item;
}

