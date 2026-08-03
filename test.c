#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function Prototypes (using Node** so functions can modify main's head pointer)
Node* createLL(Node *head);
void traverse(Node *head);
void insertBeginning(int value, Node **head);
void insertEnd(int value, Node **head);
void insertPosition(int value, int pos, Node **head);
void deleteBeginning(Node **head);
void deleteEnd(Node **head);
void deletePosition(int pos, Node **head);
void freeLL(Node **head);

int main(void) {
    Node *head = NULL;
    int choice, value, pos;

    while (true) {
        printf("\nLinked List Demo Program:\n");
        printf("--------------------------\n");
        printf("1. Create a Linked List\n");
        printf("2. Traverse the Linked List\n");
        printf("3. Insert an element\n");
        printf("4. Delete an element\n");
        printf("5. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice (1/2/3/4/5): ");
        if (scanf("%d", &choice) != 1) break;
        printf("--------------------------\n");

        switch (choice) {
            case 1:
                head = createLL(head);
                break;

            case 2:
                traverse(head);
                break;

            case 3: {
                printf("Please enter a value to insert: ");
                scanf("%d", &value);
                printf("--------------------------\n");
                printf("Please choose an insertion operation:\n");
                printf("--------------------------\n");
                printf("1. Insert at beginning\n");
                printf("2. Insert at the end\n");
                printf("3. Insert at a particular position\n");
                printf("4. Go back to main menu\n");
                printf("--------------------------\n");
                printf("Enter your choice (1/2/3/4): ");
                scanf("%d", &choice);
                printf("--------------------------\n");

                switch (choice) {
                    case 1:
                        insertBeginning(value, &head);
                        break;
                    case 2:
                        insertEnd(value, &head);
                        break;
                    case 3:
                        printf("Please enter the position (1-based) to insert into: ");
                        scanf("%d", &pos);
                        insertPosition(value, pos, &head);
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid entry!\n");
                        break;
                }
                break; // Break for case 3 of outer switch
            }

            case 4: {
                printf("--------------------------\n");
                printf("Please choose a deletion operation:\n");
                printf("--------------------------\n");
                printf("1. Delete from the beginning\n");
                printf("2. Delete from the end\n");
                printf("3. Delete from a particular position\n");
                printf("4. Go back to main menu\n");
                printf("--------------------------\n");
                printf("Enter your choice (1/2/3/4): ");
                scanf("%d", &choice);
                printf("--------------------------\n");

                switch (choice) {
                    case 1:
                        deleteBeginning(&head);
                        break;
                    case 2:
                        deleteEnd(&head);
                        break;
                    case 3:
                        printf("Please enter the position (1-based) to delete from: ");
                        scanf("%d", &pos);       
                        deletePosition(pos, &head);
                        break;
                    case 4:
                        break;
                    default:
                        printf("Invalid entry!\n");
                        break;
                }
                break; // Break for case 4 of outer switch
            }

            case 5:
                freeLL(&head);
                printf("Memory freed. Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice, please try again!\n");
                break;
        }
    }
    return 0;
}

// Create initial list root node
Node* createLL(Node *head) {
    if (head != NULL) {
        printf("Linked list already exists!\n");
        return head;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int data;
    printf("Enter initial head data: ");
    scanf("%d", &data);

    newNode->data = data;
    newNode->next = NULL;
    printf("List initialized successfully.\n");
    return newNode;
}

// Print all elements of the linked list
void traverse(Node *head) {
    if (head == NULL) {
        printf("Linked List is empty!\n");
        return;
    }

    Node *temp = head;
    printf("List contents: ");
    while (temp != NULL) {
        printf("[%d] -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Insert node at head
void insertBeginning(int value, Node **head) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
    printf("Inserted %d at beginning.\n", value);
}

// Insert node at tail
void insertEnd(int value, Node **head) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Inserted %d at end.\n", value);
}

// Insert node at specific 1-based index position
void insertPosition(int value, int pos, Node **head) {
    if (pos < 1) {
        printf("Invalid position! Position must be >= 1.\n");
        return;
    }

    if (pos == 1) {
        insertBeginning(value, head);
        return;
    }

    Node *temp = *head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds!\n");
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", value, pos);
}

// Delete head node
void deleteBeginning(Node **head) {
    if (*head == NULL) {
        printf("List is already empty!\n");
        return;
    }

    Node *temp = *head;
    *head = (*head)->next;
    printf("Deleted value: %d\n", temp->data);
    free(temp);
}

// Delete tail node
void deleteEnd(Node **head) {
    if (*head == NULL) {
        printf("List is already empty!\n");
        return;
    }

    Node *temp = *head;

    // Single node case
    if (temp->next == NULL) {
        printf("Deleted value: %d\n", temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    // Traverse to second to last node
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    printf("Deleted value: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

// Delete node at specific 1-based index position
void deletePosition(int pos, Node **head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }

    if (pos < 1) {
        printf("Invalid position!\n");
        return;
    }

    if (pos == 1) {
        deleteBeginning(head);
        return;
    }

    Node *temp = *head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds!\n");
        return;
    }

    Node *toDelete = temp->next;
    temp->next = toDelete->next;
    printf("Deleted value: %d\n", toDelete->data);
    free(toDelete);
}

// Deallocate entire list memory
void freeLL(Node **head) {
    Node *current = *head;
    Node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *head = NULL;
}