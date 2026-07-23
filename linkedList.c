#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value);
void printList(Node* head);
void freeLinkedList(Node* head);

int main(void) {
    Node* head = createNode(10);
    Node* second = createNode(20);
    Node* third = createNode(30);

    head->next = second;
    second->next = third;

    printList(head);

    freeLinkedList(head);
    head = NULL; // Prevents accidental reuse
}

Node* createNode(int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

void printList(Node* head) {
    Node* current = head; // Starts at head

    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next; // Moves to next node
    }

    printf("NULL\n");
}

void freeLinkedList(Node* head) {
    Node* current = head; // Visiting head
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next; // save next node's address before freeing current
        free(current); // free current node
        current = nextNode; // move to next saved node
    }

    printf("Linked List has been released to heap!\n");
}