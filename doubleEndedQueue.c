#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n = 0, f = -1, r = -1;

int* createDeque(int);
void enqueue_rear(int*);
void enqueue_front(int*);
int dequeue_rear(int*);
int dequeue_front(int*);
void peek(int*);

int main(void) {
    
    printf("Static Array Deque Demo Program\n");
    printf("--------------------------\n");

    int choice;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int* Deque = createDeque(n);

    while (true) {
        printf("--------------------------\n");
        printf("1. Enqueue (Regular)\n");
        printf("2. Dequeue (Regular)\n");
        printf("3. Enqueue (Front-end)\n");
        printf("4. Dequeue (Rear-end)\n");
        printf("5. Peek \n");
        printf("6. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        printf("--------------------------\n");

        switch (choice) {
            case 1:
                enqueue_rear(Deque);
                break;
            case 2: {
                int item = dequeue_front(Deque);
                if (item != -1) {
                    printf("Dequeued item: %d\n", item);
                }
                break;
            }
            case 3:
                enqueue_front(Deque);
                break;
            case 4: {
                int item = dequeue_rear(Deque);
                if (item != -1) {
                    printf("Dequeued item: %d\n", item);
                }
                break;
            }
            case 5:
                peek(Deque);
                break;
            case 6:
                free(Deque);
                return 0;
            default:
                printf("Invalid entry, please try again!\n");
                break;
        }
    }
}

int* createDeque(int n) {
    int* Deque = (int*)malloc(n * sizeof(int));

    if (Deque == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    f = -1; 
    r = -1;
    return Deque;
}

void enqueue_rear(int* Deque) {
    // Check Overflow
    if (r == n - 1) {
        printf("Overflow! Deque is full.\n");
        return;
    }

    // First element insertion
    if (f == -1) {
        f = 0;
    }

    int item;
    printf("Enter element to enqueue: ");
    scanf("%d", &item);
    
    r++;
    Deque[r] = item;
    printf("Enqueued %d successfully.\n", item);
}

void enqueue_front(int* Deque) {
    // Check Overflow
    if (f == 0) {
        printf("Overflow! Cannot enqueue at front.\n");
        return;
    }
    
    // Check if we're enqueue-ing the very first element
    if (f == -1) {
        f = r = 0; // Initialize both pointers to 0
    } else {
        f--; // Decrement f in regular conditions
    } 

    int item;
    printf("Enter element to enqueue: ");
    scanf("%d", &item);
    
    Deque[f] = item;
}

int dequeue_front(int* Deque) {
    // Check Underflow
    if (f == -1 || f > r) {
        printf("Underflow! Deque is empty.\n");
        return -1;
    }

    // Dequeued element
    int item = Deque[f];

    // Reset Deque
    if (f == r) {
        f = -1;
        r = -1;
    } else {
        f++; // Move front forward
    }

    return item;
}

int dequeue_rear(int* Deque) {
    // Check for "special" underflow
    if (f == -1) {
        printf("Underflow! Deque is empty.\n");
        return -1;
    }

    // Dequeued element
    int item = Deque[r];
    
    // Check if we're dequeue-ing the very last element
    if (f == r) {
        f = r = -1;
    } else {
        r--; // Decrement rear at normal conditions
    }

    return item;
}

void peek(int* Deque) {

    // Check for underflow
    if (f == -1) {
        printf("Deque empty! Nothing to see here!\n");
        return;
    }

    // Printing elements
    for (int i = f; i < r + 1; i++) {
        printf("%d ", Deque[i]);
    } printf("\n");
}