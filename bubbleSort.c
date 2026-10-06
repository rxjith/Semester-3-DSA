#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int arr[MAX];

void read(int n) {
    printf("------------------------------------\n");
    printf("Enter %d elements into ARR:\n", n);
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("------------------------------------\n");
    printf("%d elements inserted into array!\n", n);
}

void bubbleSort(int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Array sorted using bubble sort!\n");
}

void display(int arr[], int n) {
    printf("Array contents: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice, n;

    printf("Bubble Sort Implementation:\n");
    while (1) {
        printf("------------------------------------\n");
        printf("1. Read elements into array\n");
        printf("2. Display unsorted array\n");
        printf("3. Sort array (using bubble sort)\n");
        printf("4. Display sorted array\n");
        printf("5. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        printf("------------------------------------\n");

        switch (choice) {
            case 1:
                printf("Enter n: ");
                scanf("%d", &n);
                read(n);
                break;
            case 2:
                display(arr, n);
                break;
            case 3:
                bubbleSort(n);
                break;
            case 4:
                display(arr, n);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice, please enter a choice (1-5)!\n");
        }
    }
}
