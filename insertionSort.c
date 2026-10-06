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

void insertionSort(int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void display(int arr[], int n) {
    printf("Array contents: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice, n;

    printf("Insertion Sort Implementation:\n");
    while (1) {
        printf("------------------------------------\n");
        printf("1. Read elements into array\n");
        printf("2. Display unsorted array\n");
        printf("3. Sort array (using insertion sort)\n");
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
                insertionSort(n);
                printf("Array sorted using insertion sort!\n");
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
