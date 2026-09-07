// Circular Doubly Linked List Demo Program
// Name: Rojith Jinenth
// Class: CSE-B, 2025-2029

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node *head = NULL, *tail = NULL;
int listSize = 0;

Node* createNode(int value);
void insertElement(void);
void insertBeginning(int value);
void insertIndex(int value, int index);
void insertEnd(int value);

void deleteElement(void);
void deleteBeginning(void);
void deleteIndex(int index);
void deleteEnd(void);

void displayDLL(void);
void freeDLL(void);

int main(void) {
    int choice;
    
    printf("Circular Doubly Linked List Manager\n");
    
    while (1) {
        printf("-------------------------------------------\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Display DLL\n");
        printf("4. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1) break;
        printf("-------------------------------------------\n");
        
        switch (choice) {
            case 1:
                insertElement();
                break;
            case 2: 
                deleteElement();
                break;
            case 3:
                displayDLL();
                break;
            case 4:
                freeDLL();
                exit(0);
            default:
                printf("Invalid choice, please select between 1-4.\n");
        }
    }
    return 0;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertBeginning(int value) {
    Node* newNode = createNode(value);
    
    if (head == NULL) {
        head = tail = newNode;
        head->next = head;
        head->prev = head;
    } else {
        newNode->next = head;
        newNode->prev = tail;
        head->prev = newNode;
        tail->next = newNode;
        head = newNode;
    }
    listSize++;
    printf("%d inserted at the beginning (index 0)!\n", value);
}

void insertEnd(int value) {
    if (head == NULL) {
        insertBeginning(value);
        return;
    }
    
    Node* newNode = createNode(value);
    newNode->prev = tail;
    newNode->next = head;
    tail->next = newNode;
    head->prev = newNode;
    tail = newNode;
    
    listSize++;
    printf("%d inserted at the end (index %d)!\n", value, listSize - 1);
}

void insertIndex(int value, int index) {
    Node* temp = head;
    
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    
    Node* newNode = createNode(value);
    Node* prevNode = temp->prev;
    
    newNode->next = temp;
    newNode->prev = prevNode;
    prevNode->next = newNode;
    temp->prev = newNode;
    
    listSize++;
    printf("%d inserted at index %d!\n", value, index); 
}

void insertElement(void) {
    int index, value;
    
    printf("Enter index to insert into (0 to %d): ", listSize);
    scanf("%d", &index);
    
    if (index < 0 || index > listSize) {
        printf("Invalid index! Allowed range: 0 to %d\n", listSize);
        return;
    }
    
    printf("Enter value to insert: ");
    scanf("%d", &value);
    
    if (index == 0) {
        insertBeginning(value);
    } else if (index == listSize) {
        insertEnd(value);
    } else {
        insertIndex(value, index);
    }
}

void deleteBeginning(void) {
    if (head == NULL) {
        printf("List is empty, nothing to delete.\n");
        return;
    }
    
    Node* temp = head;
    int deletedVal = temp->data;
    
    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    
    free(temp);
    listSize--;
    printf("%d was deleted from index 0!\n", deletedVal);
}

void deleteEnd(void) {
    if (tail == NULL) {
        printf("List is empty, nothing to delete.\n");
        return;
    }
    
    if (head == tail) {
        deleteBeginning();
        return;
    }
    
    Node* temp = tail;
    int deletedVal = temp->data;
    
    tail = tail->prev;
    tail->next = head;
    head->prev = tail;
    
    free(temp);
    listSize--;
    printf("%d was deleted from the end (index %d)!\n", deletedVal, listSize);
}

void deleteIndex(int index) {
    Node* temp = head;
    
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    
    int deletedVal = temp->data;
    Node* prevNode = temp->prev;
    Node* nextNode = temp->next;
    
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    
    free(temp);
    listSize--;
    printf("%d was deleted from index %d!\n", deletedVal, index);
}

void deleteElement(void) {
    if (listSize == 0) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    
    int index;
    printf("Enter index to delete from (0 to %d): ", listSize - 1);
    scanf("%d", &index);
    
    if (index < 0 || index >= listSize) {
        printf("Invalid index! Allowed range: 0 to %d\n", listSize - 1);
        return;
    }
    
    if (index == 0) {
        deleteBeginning();
    } else if (index == listSize - 1) {
        deleteEnd();
    } else {
        deleteIndex(index);
    }
}

void displayDLL(void) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = head;
    printf("DLL Elements: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

void freeDLL(void) {
    if (head == NULL) return;
    
    Node* current = head;
    Node* nextNode;
    
    for (int i = 0; i < listSize; i++) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    
    head = tail = NULL;
    listSize = 0;
    printf("DLL was freed successfully!\n");
}