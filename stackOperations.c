#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    
    printf("Stack Operations Demonstration Program");
    
    int choice, *stack = NULL, size = 0;

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

