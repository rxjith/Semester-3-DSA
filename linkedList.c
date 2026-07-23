#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

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