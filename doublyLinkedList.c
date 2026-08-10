#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next, *prev;
} Node;

int n = 0;
Node *head, *tail;

Node* createDLL(void);
void printDLL(void);
void insertBeginning(int val);
void insertPos(int val, int pos);
void insertEnd(int val);
void insert(void);
void deleteBeginning(void);
void deletePos(int pos);
void deleteEnd(void);
void delete(void);
void freeDLL(void);

int main(void) {
    int choice;

    printf("---------------------------------------------\n");
    printf("Doubly Linked List Demo Program\n");

    while (1) {
        printf("---------------------------------------------\n");
        printf("1. Create a Doubly Linked List\n");
        printf("2. Print DLL\n");
        printf("3. Insert an element into the DLL\n");
        printf("   3.1. Enter 1 to insert 1st element\n");
        printf("   3.2. Enter n to insert nth element\n");
        printf("   3.3. Enter any other to insert at that index\n");
        printf("4. Delete an element into the DLL\n");
        printf("   4.1. Enter 1 to delete 1st element\n");
        printf("   4.2. Enter n to delete nth element\n");
        printf("   4.3. Enter any other to delete at that index\n");
        printf("5. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        printf("---------------------------------------------\n");

        switch (choice) {
            case 1:
                createDLL();
                break;
            case 2:
                printDLL();
                break;
            case 3:
                insert();
                break;
            case 4:
                delete();
                break;
            case 5:
                freeDLL();
                return 0;
            default:
                printf("Invalid choice! Please try again!\n");
        }
    }    
}

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    n++;

    return newNode;
}

Node* createDLL() {
    int count; 

    if (head != NULL) {
        printf("A DLL already exists!\n");
        return NULL;
    }

    printf("Enter # of elements you wanna enter into the Linked List: ");
    scanf("%d", &count);

    if (count <= 0) {
        printf("Please enter a positive integer greater than 0!\n");
        return NULL;
    }

    head = NULL;
    tail = NULL;

    for (int i = 0; i < count; i++) {
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
            newNode->prev = tail;
            tail = newNode;
        }
    }

    return head;
}

void printDLL(void) {
    if (head == NULL) {
        printf("DLL does not exist, nothing to see here!\n");
        return;
    }

    Node *temp = head;

    printf("DLL contents: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    } printf("\n");
}

void insertBeginning(int val) {
    Node *newNode = createNode(val);

    if (newNode == NULL) {
        printf("Insertion unsuccessful, memory allocation failed!\n");
        return;
    }

    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    printf("%d inserted successfully!\n", val);
}

void insertPos(int val, int pos) {
    Node* newNode = createNode(val);

    if (newNode == NULL) {
        printf("Insertion unsuccessful, memory allocation failed!\n");
        return;
    }

    Node* temp = head;
    int i = 0;

    while (i < pos - 1 && temp != NULL) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position out of bounds!\n");
        free(newNode);
        n--; 
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    } else {
        tail = newNode;
    }
    temp->next = newNode;

    printf("%d inserted at position %d successfully!\n", val, pos);
}

void insertEnd(int val) {
    Node* newNode = createNode(val);

    if (newNode == NULL) {
        printf("Insertion unsuccessful, memory allocation failed!\n");
        return;
    }

    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    printf("%d inserted successfully!\n", val);
}

void insert(void) {
    int val, pos;

    printf("Enter element to insert into DLL: ");
    scanf("%d", &val);
    printf("---------------------------------------------\n");
    printf("Enter position to insert into: ");
    scanf("%d", &pos);
    printf("---------------------------------------------\n");

    if (pos < 0 || pos > n) {
        printf("Invalid position! Valid insertion index is from 0 to %d!\n", n);
        return;
    } else if (pos == 0) {
        insertBeginning(val);
    } else if (pos == n) {
        insertEnd(val);
    } else {
        insertPos(val, pos);
    }
}

void deleteBeginning(void) {
    if (head == NULL) {
        printf("DLL does not exist!\n");
        return;
    }

    Node *temp = head;

    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }

    n--;
    printf("%d deleted successfully!\n", temp->data);
    free(temp);
}

void deletePos(int pos) {
    if (head == NULL) {
        printf("DLL does not exist!\n");
        return;
    }

    Node *temp = head;
    int i = 0;

    while (i < pos) {
        temp = temp->next;
        i++;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds!\n", pos);
        return;
    }

    temp->prev->next = temp->next;

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        tail = temp->prev;
    }

    n--;
    printf("%d deleted successfully from position %d!\n", temp->data, pos);
    free(temp);
}

void deleteEnd(void) {
    if (tail == NULL) {
        printf("DLL does not exist!\n");
        return;
    }

    Node *temp = tail;

    if (head == tail) {
        head = tail = NULL;
    } else {
        tail = tail->prev;
        tail->next = NULL;
    }

    n--;
    printf("%d deleted successfully!\n", temp->data);
    free(temp);
}

void delete(void) {
    if (n == 0 || head == NULL) {
        printf("DLL is empty! Nothing to delete.\n");
        return;
    }

    int pos;

    printf("Enter position of element to delete: ");
    scanf("%d", &pos);
    printf("---------------------------------------------\n");
    
    if (pos < 0 || pos >= n) {
        printf("Position out of bounds! Valid range is from 0 to %d!\n", n - 1);
        return;
    } else if (pos == 0) {
        deleteBeginning();
    } else if (pos == n - 1) {
        deleteEnd();
    } else {
        deletePos(pos);
    }
}

void freeDLL(void) {
    if (head == NULL) {
        printf("Nothing to free here, DLL does not exist!\n");
        return;
    }

    Node *current = head;

    while (current != NULL) {
        Node *nextNode = current->next;
        free(current);
        current = nextNode;
    }

    head = tail = NULL;
    n = 0;
    printf("DLL was freed successfully!\n");
}