// Uses a more intuitive bucket-sort-esque sorting technique using the given array and
// a array of "buckets" which is just an array of Singly Linked Lists which can be
// accessed using the FIFO principle to produce the intermediate/final sorted arrays.

#include <stdio.h>
#include <stdlib.h>
#define MAX 8

int arr[MAX] = {170, 45, 75, 90, 802, 24, 2, 66};

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *bucket[10] = {NULL};

int checkPasses(void) {
    int max = arr[0];

    for (int i = 1; i < MAX; i++) {
        if (arr[i] > max) max = arr[i];
    }

    int passes = 0;

    while (max > 0) {
        passes++;
        max /= 10;
    }
    return passes;
}

void bucketInserter(int val, int exp) {
    int pos = (val / exp) % 10;
    Node *newNode = malloc(sizeof(Node));

    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->data = val;
    newNode->next = NULL;

    if (bucket[pos] == NULL) {
        bucket[pos] = newNode;
    }
    else {
        Node *temp = bucket[pos];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void bucketizer(int exp) {
    for (int i = 0; i < MAX; i++) {
        bucketInserter(arr[i], exp);
    }
}

void collector(void) {
    int i = 0, j = 0;
    while (i < 10) {
        if (bucket[i] != NULL) {
            Node* temp = bucket[i];
            while (temp != NULL) {
                arr[j++] = temp->data;
                Node *next = temp->next;
                free(temp);
                temp = next;
            }
            bucket[i] = NULL;
        }
        i++;
    }
}

void radixSort(void) {
    int passes = checkPasses();
    int exp = 1;

    for (int i = 0; i < passes; i++) {
        bucketizer(exp);
        collector();
        exp *= 10;
    }
}

void displayArr(void) {
    printf("arr: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice;

    printf("Radix Sort Implementation:\n");

    while (1) {
        printf("---------------------------------------------\n");
        printf("1. Sort using Radix Sort\n");
        printf("2. Display array\n");
        printf("3. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice (1/2/3): ");
        scanf("%d", &choice);
        printf("---------------------------------------------\n");

        switch (choice) {
            case 1:
                radixSort();
                printf("Array sorted!\n");
                printf("---------------------------------------------\n");
                displayArr();
                break;
            case 2:
                displayArr();
                break;
            case 3:
                printf("Exiting program...\nExited!\n");
                printf("---------------------------------------------\n");
                exit(0);
            default: printf("Invalid choice, please enter (1-3) only!\n");
        }
    }
}
