// Take a sequence of integers from the user to construct a singly linked list and process it in four steps:

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* head = NULL;

/* 1. Partition the list in-place so all even numbers appear at the beginning and all odd numbers at the end
Example: Input [5, 12, 3, 8, 1] becomes [12, 8, 5, 3, 1]. */

Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));

    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

int isPalindrome(int num) {
    if (num < 0) return 0;
    int original = num;
    int reversed = 0;

    while (num > 0) {
        reversed = (reversed * 10) + (num % 10);
        num /= 10;
    }
    
    return original == reversed;
}

Node* partitionEvenOdd(Node* head) {
    if (!head || !head->next) return head;

    Node *evenHead = NULL, *evenTail = NULL;
    Node *oddHead = NULL, *oddTail = NULL;
    Node* current = NULL;

    while (current != NULL) {
        Node* nextNode = current->next;
        current->next = NULL;

        if (current->data % 2 == 0) {
            if (!evenHead) {
                evenHead = evenTail = current;
            } else {
                evenTail->next = current;
                evenTail = current;
            }
        } else {
            if (!oddHead) {
                oddHead = oddTail = current;
            } else {
                oddTail->next = current;
                oddTail = current;
            }
        }

        current = nextNode;
    }

    if (evenHead != NULL) {
        evenTail->next = oddHead;
        return evenHead;
    }

    return oddHead;
}

/* 2. Sort the even and odd sub-lists independently in ascending order within the single list structure
Example: Input [12, 8, 5, 3, 1] becomes [8, 12, 1, 3, 5]. */

void sortList(Node* head, int count) {
    if (count <= 1 || !head) return;

    for (int i = 0; i < count - 1; i++) {
        Node* curr = head;
        for (int j = 0; j < count - 1 - i; j++) {
            if (curr->next != NULL && curr->data > curr->next->data) {
                int temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
            }
            curr = curr->next;
        }
    }
}

void sortSubLists(Node* head) {
    if (!head) return;

    int evenCount = 0;
    Node* current = head;

    while (current != NULL && current->data % 2 == 0) {
        evenCount++;
        current = current->data;
    }

    Node* oddHead = current;

    int oddCount = 0;
    while (current != NULL) {
        oddCount++;
        current = current->next;
    }

    sortList(head, evenCount);
    sortList(oddHead, oddCount);
}

/* 3. Traverse the updated list to identify and display all palindromic numbers (including single-digit integers)
Example: Input [8, 121, 14, 3, 52] outputs 8, 121, 3. */

void printPalindrome(Node* head) {
    printf("Palindrome Numbers: ");
    Node* current = head;
    int first = 1;

    while (current != NULL) {
        if (isPalindrome(current->data)) {
            if (!first) printf(", ");
            printf("%d", current->data);
            first = 0;
        }
        current = current->next;
    } printf("\n");
}

/* 4. select every alternate node starting from the head element (indices 0, 2, 4, ...) and 
      output those values in reverse order.
      Example: [8, 12, 1, 3, 5] gives [8, 1, 5], which outputs in reverse as  5, 1, 8 */

void printAlternateReverseHelper(Node* current, int index) {
    if (current == NULL) return;

    printAlternateReverseHelper(current->next, index + 1);

    if (index % 2 == 0) {
        printf("%d ", current->data);
    }
}

void printAlternateReversed(Node* head) {
    printf("Alternate Nodes in Reverse: ");
    printAlternateReverseHelper(head, 0);
    printf("\n");
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
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    Node* head = NULL;
    Node* tail = NULL;

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        Node* newNode = createNode(val);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Step 1: Partition Even numbers before Odd numbers
    head = partitionEvenOdd(head);

    // Step 2: Sort even and odd sub-lists in ascending order
    sortSubLists(head);

    // Step 3: Find and print palindromic numbers
    printPalindromes(head);

    // Step 4: Output alternate elements in reverse order
    printAlternateReversed(head);

    freeList(head);
    return 0;
}