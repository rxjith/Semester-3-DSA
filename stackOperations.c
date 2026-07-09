#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
                pop(stack, size);
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid entry, please try again!\n");
        }

        return 0;
    }
}

bool isFull(int* stack, int size, int* top) {

    if (*top == size - 1) {
        printf("Overflow.\n");
        return true;
    } return false;
}

bool isEmpty(int* stack, int size, int* top) {
    
    if (*top == -1) {
        printf("Underflow.\n");
        return true;
    } return false;
}

void createStack(int* stack) {

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
