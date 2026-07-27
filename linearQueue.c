#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n = 0, f = -1, r = -1;

int* createQueue(int);
void enqueue(int*);
int dequeue(int*);
void peek(int*);

int main(void) {
    
    printf("Linear Queue Demo Program\n");
    printf("--------------------------\n");

    int choice;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int* queue = createQueue(n);

    while (true) {
        printf("--------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice (1/2/3/4): ");
        scanf("%d", &choice);
        printf("--------------------------\n");

        switch (choice) {
            case 1:
                enqueue(queue);
                break;
            case 2: {
                int item = dequeue(queue);
                if (item != -1) {
                    printf("Dequeued item: %d\n", item);
                }
                break;
            }
            case 3:
                peek(queue);
                break;
            case 4:
                free(queue);
                return 0;
            default:
                printf("Invalid entry, please try again!\n");
                break;
        }
    }
}

int* createQueue(int n) {
    int* queue = (int*)malloc(n * sizeof(int));

    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return queue;
}

void enqueue(int* queue) {
    // Check Overflow
    if (r == n - 1) {
        printf("Overflow! Queue is full.\n");
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
    queue[r] = item;
    printf("Enqueued %d successfully.\n", item);
}

int dequeue(int* queue) {
    // Check Underflow
    if (f == -1 || f > r) {
        printf("Underflow! Queue is empty.\n");
        return -1;
    }

    int item = queue[f];

    // Reset queue
    if (f == r) {
        f = -1;
        r = -1;
    } else {
        f++; // Move front forward
    }

    return item;
}

void peek(int* queue) {

    if (f == -1) {
        printf("Queue empty! Nothing to see here!\n");
        return;
    }

    for (int i = f; i < r + 1; i++) {
        printf("%d ", queue[i]);
    } printf("\n");
}