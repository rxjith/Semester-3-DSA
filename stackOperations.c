#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isFull(int* , int);
bool isempty(int* );
void createStack(int* );
void push(int*, int* );
int pop(int*, int* );

int main(void) {
    
    printf("Stack Operations Demonstration Program");
    
    int choice, *stack = NULL, *top = -1, size = 0;

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
                createStack(stack);
                size = sizeof(stack)/sizeof(int);
                break;
            case 2:
                push(stack, size);
                break;
            case 3:
                if (!isEmpty) {
                    int poppedItem = pop(stack, size);
                    int choice2;

                    printf("1. Print item\n");
                    printf("2. Delete item\n");
                    printf("---------------------------------------------\n");
                    printf("Enter your choice (1/2): ");
                    scanf("%d", &choice2);
                    printf("---------------------------------------------\n");

                    switch (choice2) {
                        case 1:
                            printf("Item: %d", poppedItem);
                            break;
                        case 2:
                            printf("Item has been deleted!\n");
                            break;
                        default:
                            printf("Invalid entry, item has been deleted!\n");
                    }    
                }
                break;
            case 4:
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

    if (*top == size - 1) {
        return true;
    } return false;
}

bool isEmpty(int* top) {
    
    if (*top == -1) {
        return true;
    } return false;
}

void createStack(int* stack) {

    if (stack != NULL) {
        printf("Stack has already been created!\n");
        return;
    }

    int n;
    printf("---------------------------------------------\n");
    printf("Enter # of member-spaces you want to allocate: ");
    scanf("%d", &n);
    printf("---------------------------------------------\n");
    stack = (int*) malloc(n * sizeof(int));

    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Stack memory allocated successfully!\n");
}

void push(int* stack, int* top) {

    if (isFull) {
        printf("Overflow\n");
        return;
    }

    int item;

    printf("Enter element to push into the stack: ");
    scanf("%d", &item);
    stack[++(*top)] = item;
    printf("---------------------------------------------\n");
    printf("%d pushed successfully!\n", item);
    return;
}

int pop(int* stack, int* top) {
    if (isEmpty) {
        printf("Underflow\n");
        return;
    }

    int item;
    item = stack[*top];
    (*top)--;
    printf("Item popped successfully!\n");
    return item;
}

