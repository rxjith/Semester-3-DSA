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

void merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void display(int n) {
    printf("Array contents: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice, n;

    printf("Merge Sort Implementation:\n");
    while (1) {
        printf("------------------------------------\n");
        printf("1. Read elements into array\n");
        printf("2. Display unsorted array\n");
        printf("3. Sort array (using merge sort)\n");
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
                display(n);
                break;
            case 3:
                mergeSort(0, n - 1);
                printf("Array sorted using merge sort!\n");
                break;
            case 4:
                display(n);
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice, please enter a choice (1-5)!\n");
        }
    }
}
