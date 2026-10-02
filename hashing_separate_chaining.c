// Hash Function: H(k) = k % 10, h = 10 (0 to 9)

#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // table size

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* hashTable[MAX] = {NULL};

int hashedEntries = 0; // counter to keep tab on the # of hashed entries to later compute load factor

int hash(int key) {
    return key % MAX;
}

Node* createNode(int key) {
    Node* newNode = malloc(sizeof(Node));

    if (!newNode) {
        printf("--------------------------\n");
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newNode->data = key;
    newNode->next = NULL;
    hashedEntries++;
    return newNode;
}

void openHasher(int key) {
    int index = hash(key);
    
    if (hashTable[index] == NULL) {
        hashTable[index] = createNode(key);
        return;
    } else {
        Node* temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = createNode(key);
    }
    printf("%d hashed successfully!\n", key);
}

void displayHashTable(void) {
    if (hashedEntries == 0) {
        printf("Hashtable is empty!\n");
        return;
    }

    for (int i = 0; i < MAX; i++) {
        printf("%d: ", i);
        Node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}



int main(void) {
    int choice, key;
    printf("Open Hashing Simulator:\n");
    while (1) {    
        printf("--------------------------\n");
        printf("1. Enter an element into hash table\n");
        printf("2. Display hash table\n");
        printf("3. Compute load factor\n");
        printf("4. Exit\n");
        printf("--------------------------\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        printf("--------------------------\n");

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                openHasher(key);
                break;

            case 2:
                printf("Hash Table Contents:\n");
                displayHashTable();
                break;
            
            case 3:
                printf("Load Factor: %.2f\n", hashedEntries / 10.00);
                break;
        
            case 4:
                printf("Exiting program...\n");
                printf("--------------------------\n");
                exit(0);
            
            default:
                printf("Invalid entry, please pick from (1-4)!\n");
        }
    }
}