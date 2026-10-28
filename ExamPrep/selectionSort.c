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

void selectionSort(void) {
    for (int i = 0; i < MAX - 1; i++) {
        int min = i;

        for (int j = i + 1; j < MAX; j++) {
            if (arr[j] < arr[min]) min = j;
        }

        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
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

    printf("Selection Sort Implementation:\n");
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
                selectionSort();
                display();
                break;
            case 3:
                return 0;
            default: printf("Invalid choice, please choose between 1-3 only!\n");
        }
    }
}
