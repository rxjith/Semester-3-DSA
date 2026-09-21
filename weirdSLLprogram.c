#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char string[20];
    struct Node* next;
} Node;

Node* createNode(const char* str) {
    Node* newNode = malloc(sizeof(Node));

    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strncpy(newNode->string, str, sizeof(newNode->string) - 1);
    newNode->string[sizeof(newNode->string) - 1] = '\0';
    newNode->next = NULL;
    return newNode;
}

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

Node* processLL(char arr[][20], int size) {
    if (size == 0) return NULL;

    Node* head = createNode(arr[0]);
    Node* current = head;

    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }

    Node* upperHead = NULL;
    Node* upperTail = NULL;
    Node* lowerHead = NULL;
    Node* lowerTail = NULL;
    
    current = head;
    while (current != NULL) {
        Node* nextNode = current->next;
        current->next = NULL;

        if (isupper((unsigned char)current->string[0])) {
            if (upperHead == NULL) {
                upperHead = upperTail = current;
            } else {
                upperTail->next = current;
                upperTail = current;
            }
        } else {
            if (lowerHead == NULL) {
                lowerHead = lowerTail = current;
            } else {
                lowerTail->next = current;
                lowerTail = current;
            }
        }
        current = nextNode;
    }

    if (upperHead != NULL) {
        head = upperHead;
        upperTail->next = lowerHead;
    } else {
        head = lowerHead;
    }

    current = head;
    int index = 0;

    printf("\nAlternate Reversed Words: ");
    while (current != NULL) {
        if (index % 2 == 0) {
            char temp[20];
            strcpy(temp, current->string);
            reverseString(temp);
            printf("%s", temp);

            if (current->next != NULL && current->next->next != NULL) {
                printf(", ");
            }
        }
        current = current->next;
        index++;
    } 
    printf("\n");
    return head;
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    int n;

    printf("Enter number of strings you wanna enter: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    // Stack-allocated 2D array to safely hold inputs
    char input[n][20];

    for (int i = 0; i < n; i++) {
        printf("Enter string %d: ", i + 1);
        scanf(" %19[^\n]", input[i]);
    }

    Node* head = processLL(input, n);
    freeList(head);
    return 0;
}