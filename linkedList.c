#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value);
Node* createList();
void printList(Node* head);
int searchList(Node* head, int key);
void freeLinkedList(Node* head);

int main(void) {

    Node* head = createList();
    printList(head);

    freeLinkedList(head);
    head = NULL; // Prevents accidental reuse

    return 0;
}

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    return newNode;
}

Node* createList() {
    int n;

    printf("Enter # of elements you wanna enter into the Linked List: ");
    scanf("%d", &n);

    if (n <= 0) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        int value = 0;
        printf("Enter element into node %d: ", i + 1);
        scanf("%d", &value);

        Node* newNode = createNode(value);

        if (head == NULL) {
            // first element becomes head and tail
            head = newNode;
            tail = newNode;
        } else {
            // node attaches to the end and tail gets updated
            tail->next = newNode;
            tail = tail->next;
        }
    }

    return head;
}

void printList(Node* head) {
    Node* current = head; // Starts at head

    while (current != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next; // Moves to next node
    }

    printf("NULL\n");
}

int searchList(Node* head, int key) {
    Node* current = head;
    int index = 0;

    while (current != NULL) {
        if (current->data == key) {
            return index;
        }
        current = current->next;
        index++;
    }
}

void freeLinkedList(Node* head) {
    Node* current = head; // Visiting head
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next; // save next node's address before freeing current
        free(current); // free current node
        current = nextNode; // move to next saved node
    }

    printf("Linked List has been released from heap!\n");
}