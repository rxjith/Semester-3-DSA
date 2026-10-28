#include <stdio.h>
#define MAX 10

int arr[MAX];

void readArray(void) {
    for (int i = 0; i < MAX; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("arr: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

void insertionSort(void) {
    for (int i = 1; i < MAX; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void display(void) {
    printf("Sorted arr: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice;

    printf("Insertion Sort Implementation:\n");
    while (1) {
        printf("-------------------------------------------\n");
        printf("1. Enter array elements\n2. Sort array\n3. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("-------------------------------------------\n");

        switch (choice) {
            case 1:
                readArray();
                break;
            case 2:
                insertionSort();
                display();
                break;
            case 3:
                return 0;
            default: printf("Invalid choice, please choose between 1-3 only!\n");
        }
    }
}
