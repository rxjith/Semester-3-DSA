// Implement Circular Queue using arrays.

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int cQueue[MAX];
int cFront = -1, cRear = -1;

int isCircularQueueEmpty(void);
int isCircularQueueFull(void);

void enqueue(void);
void dequeue(void);
void displayCircularQueue(void);

int main(void) {
    printf("Circular Queue Demo:\n");

    int choice;
    
    while (1) {
        printf("---------------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Circular Queue\n");
        printf("4. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice (1-4): "); scanf("%d", &choice);
        printf("---------------------------------\n");

        switch (choice) {
            case 1: enqueue(); break;
            case 2: dequeue(); break;
            case 3: displayCircularQueue(); break;
            case 4: exit(0);
            default: printf("Invalid choice, please enter a choice from 1-4 only!\n");
        }
    }
}

int isCircularQueueEmpty(void) {
    return cFront == -1;
}

int isCircularQueueFull(void) {
    return (cRear + 1) % MAX == cFront;
}

void enqueue(void) {
    if (isCircularQueueFull()) {
        printf("Circular Queue overflow!\n");
        return;
    }

    if (isCircularQueueEmpty()) {
        cFront = cRear = 0;
    } else {
        cRear = (cRear + 1) % MAX;
    }

    int val;
    printf("Enter value to enqueue: "); scanf("%d", &val);
    cQueue[cRear] = val;
    printf("%d enqueued successfully!\n", val);
    return;
}

void dequeue(void) {
    if (isCircularQueueEmpty()) {
        printf("Circular Queue underflow!\n");
        return;
    }

    int val = cQueue[cFront];
    printf("%d dequeued successfully!\n", val);

    if (cFront == cRear) {
        cFront = cRear = -1;
    } else {
        cFront = (cFront + 1) % MAX;
    }
}

void displayCircularQueue(void) {
    if (isCircularQueueEmpty()) {
        printf("Circular Queue underflow!\n");
        return;
    }

    int i = cFront;
    printf("Circular Queue contents: ");
    while (1) {
        printf("%d ", cQueue[i]);
        if (i == cRear) break;
        i = (i + 1) % MAX; 
    } printf("\n");
}