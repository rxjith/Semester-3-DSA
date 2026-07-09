#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    
    printf("Stack Operations Demonstration Program");
    
    int choice, *stack = NULL;

    while (true) {
        printf("---------------------------------------------\n");
        printf("1. Create a stack\n");
        printf("2. Grow the stack\n");
        printf("3. Push\n");
        printf("4. Pop\n");
        printf("5. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter choice (1/2/3/4/5): ");
        scanf("%d", &choice);
        printf("---------------------------------------------\n");

        switch (choice) {
            case 1:
                createStack(stack);
                break;
            case 2:
                growStack();
                break;
            case 3:
                push();
                break;
            case 4:
                pop();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid entry, please try again!\n");
        }

        return 0;
    }
}

