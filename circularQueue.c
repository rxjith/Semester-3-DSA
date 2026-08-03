#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n;

void enqueue(int[], int, int*, int*);
int dequeue(int[], int, int*, int*);
void displayQueue(int[], int, int, int);

int main(void) {

    int choice;

    printf("Circular Queue Implementation:\n");
    printf("------------------------------------------\n");
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int *queue = calloc(n, sizeof(int));

    if (queue == NULL) {
        printf("------------------------------------------\n");
        printf("Memory allocation for queue failed!\n");
        printf("------------------------------------------\n");
        exit(1);
    }

    int f = -1, r = -1;
    
    while (true) {
        printf("------------------------------------------\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display Queue\n4. Exit\n");
        printf("------------------------------------------\n");
        printf("Please enter your choice (1 / 2 / 3 / 4): ");
        scanf("%d", &choice);
        printf("------------------------------------------\n");

        switch (choice) {
            case 1:
                enqueue(queue, n, &f, &r);
                break;
            case 2:
                int item = dequeue(queue, n, &f, &r);
                if (item != -1) {
                    printf("Item: %d\n", item);
                } else {
                    printf("Queue empty! Nothing to see here!\n");
                }
                break;
            case 3:
                displayQueue(queue, n, f, r);
                break;
            case 4:
                free(queue);
                printf("Exiting program...\n");
                printf("------------------------------------------\n");
                exit(0);
            default:
                printf("INVALID choice, please try again!\n");
        }
    }

    free(queue);
    return 0;
}

void enqueue(int queue[], int SIZE, int *f, int *r)
{
    if ((*r + 1) % SIZE == *f) {
        printf("Queue Overflow\n");
        return;
    }

    int item;
    printf("Enter element: ");
    scanf("%d", &item);

    if (*f == -1) {
        *f = 0;
        *r = 0;
    }
    else {
        *r = (*r + 1) % SIZE;
    }

    queue[*r] = item;
    printf("%d was enqueued!\n", item);
}

int dequeue(int queue[], int SIZE, int *f, int *r)
{
    if (*f == -1) {
        printf("Queue Underflow\n");
        return -1;
    }

    int item = queue[*f];

    if (*f == *r) {
        *f = -1;
        *r = -1;
    }
    else {
        *f = (*f + 1) % SIZE;
    }

    return item;
}

void displayQueue(int queue[], int SIZE, int f, int r)
{
    if (f == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue Elements: ");

    int i = f;

    while (true) {
        printf("%d ", queue[i]);

        if (i == r) {
            break;
        }

        i = (i + 1) % SIZE;
    }
    printf("\n");
}