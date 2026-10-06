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

int partition(int p, int r) {
    int x = arr[r];
    int i = p - 1;

    for (int j = p; j < r;j++) {
        if (arr[j] <= x) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}

void quickSort(int p, int r) {
    if (p < r) {
        int q = partition(p, r);
        quickSort(p, q - 1);
        quickSort(q + 1, r);
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

    printf("Quick Sort Implementation:\n");
    while (1) {
        printf("------------------------------------\n");
        printf("1. Read elements into array\n");
        printf("2. Display unsorted array\n");
        printf("3. Sort array (using quick sort)\n");
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
                quickSort(0, n - 1);
                printf("Array sorted using quick sort!\n");
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
