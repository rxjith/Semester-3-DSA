#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *front = NULL, *rear = NULL;

void enqueue(int value);
int dequeue();
void display();
void freeQueue();

int main(void) {
    int choice, value, item;

    printf("Linked List representation of Queue:\n");

    while (true) {
        printf("------------------------------------\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                item = dequeue();
                if (item != -1) {
                    printf("Dequeue-d item: %d\n", item);
                }
                break;
            case 3:
                display();
                break;
            case 4:
                freeQueue();
                printf("Memory freed! Exiting program...\n");
                exit(0);
            default:
                printf("Invalid input, please try again!\n");
                break;
        }
    }
}

void enqueue(int value) {
    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed (Queue Overflow)!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
        printf("Enqueued %d\n", value);
        return;
    }

    rear->next = newNode;
    rear = newNode;

    printf("Enqueued %d\n", value);
}

int dequeue(void) {
    if (front == NULL) {
        printf("Queue underflow! Nothing to dequeue here!\n");
        return -1;
    }

    Node *temp = front;
    int item = temp->data;
    front = front->next;

    if (front == NULL) {
        rear = NULL;
    }

    free(temp);
    return item;
}

void display(void) {
    if (front == NULL) {
        printf("Queue underflow! Nothing to see here!\n");
        return;
    }

    Node *temp = front;

    printf("<FRONT> ");
    while (temp != NULL) {
        if (temp == rear) {
            printf("[%d] <REAR>", temp->data);
        } else {
            printf("[%d] -> ", temp->data);
        }
        temp = temp->next;
    } printf("\n");
}

void freeQueue(void) {
    Node *temp = front;
    while (front != NULL) {
        front = front->next;
        free(temp);
        temp = front;
    }

    front = rear = NULL;
}