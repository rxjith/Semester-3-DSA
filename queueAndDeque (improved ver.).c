// Implement Queue and DEQUEUE using arrays

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX];
int qFront = -1, qRear = -1;

int deque[MAX];
int dFront = -1, dRear = -1;

int isQueueEmpty(void);
int isQueueFull(void);

int isDequeEmpty(void);
int isDequeFull(void);

void enqueue(void);
void dequeue(void);
void displayQueue(void);

void insertFront(void);
void insertRear(void);
void deleteFront(void);
void deleteRear(void);
void displayDeque(void);

int main(void) {

    int mainChoice, subChoice;

    printf("Queue and Deque Program\n");
    
    while (1) {
        printf("---------------------------------------\n");
        printf("1. Queue Operations\n");
        printf("2. Deque Operations\n");
        printf("3. Exit\n");
        printf("---------------------------------------\n");
        printf("Enter your choice 1-3: "); scanf("%d", &mainChoice);
        printf("---------------------------------------\n");

        switch(mainChoice) {
            case 1:
                while (1) {
                    printf("Queue Menu\n");
                    printf("---------------------------------------\n");
                    printf("1. Enqueue\n");
                    printf("2. Dequeue\n");
                    printf("3. Display Queue\n");
                    printf("4. Back to main menu\n");
                    printf("---------------------------------------\n");
                    printf("Enter your choice 1-4: "); scanf("%d", &subChoice);
                    printf("---------------------------------------\n");

                    if (subChoice == 1) enqueue();
                    else if (subChoice == 2) dequeue();
                    else if (subChoice == 3) displayQueue();
                    else if (subChoice == 4) {printf("Returning to main menu...\n"); break;}
                    else printf("Invalid choice, please enter a choice from 1-4 only!\n");
                }
                break;

            case 2:
                while (1) {
                    printf("Deque Menu\n");
                    printf("---------------------------------------\n");
                    printf("1. Insert at front\n");
                    printf("2. Insert at rear\n");
                    printf("3. Delete from front\n");
                    printf("4. Delete from rear\n");
                    printf("5. Display Deque\n");
                    printf("6. Back to main menu\n");
                    printf("---------------------------------------\n");
                    printf("Enter your choice 1-6: "); scanf("%d", &subChoice);
                    printf("---------------------------------------\n");

                    if (subChoice == 1) insertFront();
                    else if (subChoice == 2) insertRear();
                    else if (subChoice == 3) deleteFront();
                    else if (subChoice == 4) deleteRear();
                    else if (subChoice == 5) displayDeque();
                    else if (subChoice == 6) {printf("Returning to main menu...\n"); break;}
                    else printf("Invalid choice, please enter a choice from 1-6 only!\n");
                }
                break;
            
            case 3:
                printf("Exiting program...\n");
                exit(0);
            
            default:
                printf("Invalid choice, please enter a choice from 1-3 only!\n");
        }
    }
}

int isQueueEmpty(void) {
    return qRear == -1 || qFront > qRear;
}

int isQueueFull(void) {
    return qRear == MAX - 1;
}

void enqueue(void) {
    int val;
    
    printf("Enter value to enqueue: "); scanf("%d", &val);
    printf("---------------------------------------\n");
    
    if (isQueueFull()) {
        printf("Queue overflow!\n");
        return;
    }

    if (isQueueEmpty()) {
        qFront = 0;
    }

    queue[++qRear] = val;
    printf("%d enqueued successfully!\n", val);
}

void dequeue(void) {
    int val;

    if (isQueueEmpty()) {
        printf("Queue underflow!\n");
        return;
    }

    printf("Dequeued element: %d\n", queue[qFront++]);

    if (qFront > qRear) qFront = qRear = -1;
}

void displayQueue(void) {
    if (isQueueEmpty()) {
        printf("Queue underflow!\n");
        return;
    }

    int i = qFront;
    printf("Queue contents: ");
    while (i <= qRear) {
        printf("%d ", queue[i++]);
    } printf("\n");
}

int isDequeEmpty(void) {
    return dFront == -1;
}

int isDequeFull(void) {
    return (dFront == 0 && dRear == MAX - 1) || (dFront == dRear - 1);
}

void insertFront(void) {
    if (isDequeFull()) {
        printf("Deque overflow!\n");
        return;
    }

    int val;

    printf("Enter val to insert at the front: "); scanf("%d", &val);
    printf("---------------------------------------\n");

    if (isDequeEmpty()) dFront = dRear = 0;
    else if (dFront == 0) dFront = MAX - 1;
    
    deque[--dFront] = val;
    printf("%d was inserted at the front!\n", val);
}

void insertRear(void) {
    if (isDequeFull()) {
        printf("Deque overflow!\n");
        return;
    }

    int val;

    printf("Enter val to insert at rear: "); scanf("%d", &val);
    printf("---------------------------------------\n");

    if (isDequeEmpty()) dFront = dRear = 0;
    deque[++dRear] = val;
    printf("%d was inserted at the rear!\n", val);
}

void deleteFront(void) {
    if (isDequeEmpty()) {
        printf("Deque underflow!\n");
        return;
    }

    printf("Dequeued element: %d", deque[dFront++]);
    
    if (dFront > dRear) dFront = dRear = -1;
}

void deleteRear(void) {
    if (isDequeEmpty()) {
        printf("Deque underflow!\n");
        return;
    }
    
    printf("Dequeued element: %d", deque[dRear--]);

    if (dFront > dRear) dFront = dRear = -1;
}

void displayDeque(void) {
    if (isDequeEmpty()) {
        printf("Deque underflow!\n");
        return;
    }

    printf("Deque contents: ");
    for (int i = dFront; i <= dRear; i++) printf("%d", deque[i]);
    printf("\n");
}