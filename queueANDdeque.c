#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Queue:
int queue[MAX];
int qFront = -1, qRear = -1;

// Deque:
int deque[MAX];
int dFront = -1, dRear = -1;

// Helper Functions:
int isQueueFull(void);
int isQueueEmpty(void);

int isDequeFull(void);
int isDequeEmpty(void);

// Linear Queue Functions:
void enqueue(int val);
void dequeue(void);
void displayQueue(void);

// Deque Functions:
void insertFront(int val);
void insertRear(int val);
void deleteFront(void);
void deleteRear(void);
void displayDeque(void);

int main(void) {
    int mainChoice, subChoice, val;
    printf("--------------------------------------\n");

    while (1) {
        printf("               MAIN MENU              \n");
        printf("--------------------------------------\n");
        printf("1. Linear Queue Operations\n");
        printf("2. Deque Operations\n");
        printf("3. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                while (1) {
                    printf("--------------------------------------\n");
                    printf("           LINEAR QUEUE MENU          \n");
                    printf("--------------------------------------\n");
                    printf("1. Enqueue\n");
                    printf("2. Dequeue\n");
                    printf("3. Display Queue\n");
                    printf("4. Back to main menu\n");
                    printf("--------------------------------------\n");
                    printf("Enter your choice (1/2/3/4): ");
                    scanf("%d", &subChoice);
                    printf("--------------------------------------\n");

                    if (subChoice == 1) {
                        printf("Enter value: ");
                        scanf("%d", &val);
                        enqueue(val);
                    } else if (subChoice == 2) {
                        dequeue();
                    } else if (subChoice == 3) {
                        displayQueue();
                    } else if (subChoice == 4) {
                        break;
                    } else {
                        printf("Invalid choice! Please try again\n");
                    }
                }
                break;
            
            case 2:
                while (1) {
                    printf("--------------------------------------\n");
                    printf("        DOUBLE ENDED QUEUE MENU       \n");
                    printf("--------------------------------------\n");
                    printf("1. Insert at front\n");
                    printf("2. Insert at rear\n");
                    printf("3. Delete at front\n");
                    printf("4. Delete at rear\n");
                    printf("5. Display\n");
                    printf("6. Back to main menu\n");
                    printf("--------------------------------------\n");
                    printf("Enter your choice (1/2/3/4/5/6): ");
                    scanf("%d", &subChoice);
                    printf("--------------------------------------\n");

                    if (subChoice == 1) {
                        printf("Enter value: ");
                        scanf("%d", &val);
                        insertFront(val);
                    } else if (subChoice == 2) {
                        printf("Enter value: ");
                        scanf("%d", &val);
                        insertRear(val);
                    } else if (subChoice == 3) {
                        deleteFront();
                    } else if (subChoice == 4) {
                        deleteRear();
                    } else if (subChoice == 5) {
                        displayDeque();
                    } else if (subChoice == 6) {
                        break;
                    } else {
                        printf("Invalid choice! Please try again\n");
                    }
                }
                break;

            case 3:
                printf("Exiting program...\n");
                exit(0);

            default: printf("Invalid choice! Please try again\n");
        }
    }

    return 0;
}

// Helper functions for Linear Queue:
int isQueueFull() {
    return qRear == MAX - 1;
}
int isQueueEmpty() {
    return qRear == -1 || qFront > qRear;
}

// Main functions for Linear Queue:
void enqueue(int val) {
    if (isQueueFull()) {
        printf("Queue Overflow!\n");
        return;
    }

    if (qFront == -1) {
        qFront = 0;
    }

    qRear++;
    queue[qRear] = val;
    printf("%d enqueued!\n", val);
}

void dequeue() {
    if (isQueueEmpty()) {
        printf("Queue Underflow\n");
        return;
    }

    printf("Dequeued element: %d\n", queue[qFront]);
    qFront++;

    if (qFront > qRear) {
        qFront = qRear = -1;
    }
}

void displayQueue() {
    if (isQueueEmpty()) {
        printf("Queue is empty, nothing to see here!\n");
        return;
    }

    printf("Queue Elements: ");
    for (int i = qFront; i <= qRear; i++) {
        printf("%d ", queue[i]);
    } printf("\n");
}

// Helper functions for Deque:
int isDequeFull() {
    return (dFront == 0 && dRear == MAX - 1) || (dFront == dRear + 1);
}

int isDequeEmpty() {
    return (dFront == -1);
}

// Main functions for Deque:
void insertFront(int val) {
    // Check Overflow
    if (isDequeFull()) {
        printf("Overflow! Deque is full.\n");
        return;
    }

    if (isDequeEmpty()) {
        dFront = dRear = 0;
    } else if (dFront == 0) {
        dFront = MAX - 1;
    } else dFront--;

    deque[dFront] = val;
    printf("%d inserted at front!\n", val);
}

void insertRear(int val) {
    // Check Overflow
    if (isDequeFull()) {
        printf("Overflow! Cannot insert at front.\n");
        return;
    }
    
    if (isDequeEmpty()) {
        dFront = dRear = 0;
    } else if (dRear == MAX - 1) {
        dRear = 0;
    } else dRear++;

    deque[dRear] = val;
    printf("%d inserted at rear!\n", val);
}

void deleteFront() {
    // Check Underflow
    if (isDequeEmpty()) {
        printf("Underflow! Deque is empty.\n");
        return;
    }

    printf("%d was removed from the front!\n", deque[dFront]);

    if (dFront == dRear) {
        dFront = dRear = -1;
    } else if (dFront == MAX - 1) {
        dFront = 0;
    } else dFront++;
}

void deleteRear() {
    if (isDequeEmpty()) {
        printf("Underflow! Deque is empty.\n");
        return;
    }

    printf("%d was removed from the rear!\n", deque[dRear]);
    
    if (dFront == dRear) {
        dFront = dRear = -1;
    } else if (dRear == 0) {
        dRear = MAX - 1;
    } else dRear--;
}

void displayDeque() {
    if (isDequeEmpty()) {
        printf("Queue underflow! Nothing to see here!\n");
        return;
    }

    printf("Deque Elements: ");
    int i = dFront;
    while (1) {
        printf("%d ", deque[i]);
        if (i == dRear) break;
        i = (i + 1) % MAX;
    } printf("\n");
}