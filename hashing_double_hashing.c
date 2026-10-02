// Hash Function: H(k) = k % 10, h = 10 (0 to 9)

#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // table size

#define EMPTY -1

int hashTable[MAX];

int hashedEntries = 0;

// ---------- HELPER FUNCTIONS -------------
int hash1(int key) {
    return key % MAX;
}

int isPrime(int n) {
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int closestPrimeToMAX() {
    for (int i = MAX - 1; i >= 2; i--) {
        if (isPrime(i))
            return i;
    }

    return EMPTY;
}

int hash2(int key) {
    int prime = closestPrimeToMAX();

    if (prime == EMPTY) {
        printf("Unable to get prime number closest to max...\n");
        exit(1);
    }
    return prime - (key % prime);
}
// -----------------------------------------

void doubleHasher(int key, int index, int i) {
    if (hashedEntries == MAX) {
        printf("Hash table is FULL!\n");
        return;
    }

    if (hashTable[index] == EMPTY) {
        hashTable[index] = key;
        hashedEntries++;
        printf("%d hashed successfully!\n", key);
        return;
    }

    i++;
    index = (hash1(key) + i * hash2(key)) % MAX;

    doubleHasher(key, index, i);
}

void displayHashTable(void) {
    if (hashedEntries == 0) {
        printf("Hashtable is empty!\n");
        return;
    }

    for (int i = 0; i < MAX; i++) {
        if (hashTable[i] != EMPTY) {
            printf("%d: %d\n", i, hashTable[i]);    
        } else {
            printf("%d: [NULL]\n", i);
        }
    } printf("\n");
}

int main(void) {
    for (int i = 0; i < MAX; i++) {
        hashTable[i] = EMPTY;
    }

    int choice, key;
    printf("Double Hashing Simulator:\n");
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
                doubleHasher(key, hash1(key), 0);
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