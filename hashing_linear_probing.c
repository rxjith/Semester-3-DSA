// Hash Function: H(k) = k % 10, h = 10 (0 to 9)

#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // table size

int hashTable[MAX] = {0};

int hashedEntries = 0;

int hash(int key) {
    return key % MAX;
}

void linearProbe(int key, int index) {
    if (hashedEntries == MAX) {
        printf("Hash table is FULL!\n");
        return;
    }

    if (hashTable[index] == 0) {
        hashTable[index] = key;
        hashedEntries++;
        printf("%d hashed successfully!\n", key);
        return;
    }
    index = (index + 1) % MAX;
    linearProbe(key, index);
}

void displayHashTable(void) {
    if (hashedEntries == 0) {
        printf("Hashtable is empty!\n");
        return;
    }

    for (int i = 0; i < MAX; i++) {
        if (hashTable[i] != 0) {
            printf("%d: %d\n", i, hashTable[i]);    
        } else {
            printf("%d: [NULL]\n", i);
        }
    } printf("\n");
}

int main(void) {
    int choice, key;
    printf("Linear Probing Simulator:\n");
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
                linearProbe(key, key % MAX);
                break;

            case 2:
                printf("Hash Table Contents:\n");
                displayHashTable();
                break;
            
            case 3:
                printf("Load Factor: %.2f\n", hashedEntries / (float) MAX);
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