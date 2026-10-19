#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int arr[MAX] = {0};

void readArray(void) {
    printf("Enter activity points into array:\n");
    printf("-------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        printf("Enter activity points awarded by activity %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("-------------------------------\n");
}

void merge(int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[start + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = start;
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

void mergeSort(int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(start, mid);
        mergeSort(mid + 1, end);
        merge(start, mid, end);
    }
}

int calculateMax(void) {
    int maxActivities, sum = 0;

    mergeSort(0, MAX - 1);
    printf("Array sorted successfully!\n");
    printf("-------------------------------\n");
    printf("Enter number of activities you can attend: ");
    scanf("%d", &maxActivities);
    printf("-------------------------------\n");
    printf("Activities you can attend:\n");
    printf("-------------------------------\n");
    for (int i = MAX - 1; i >= MAX - maxActivities; i--) {
        int count = 1;
        printf("Activity %d: %d pts\n", count++, arr[i]);
        sum += arr[i];
    }

    return sum;
}

int main(void) {
    int choice;

    printf("KTU Activity Points Calculator:\n");
    
    while (1) {
        printf("-------------------------------\n");        
        printf("1. Enter array of activity points\n");
        printf("2. Calculate the maximum number of activity points you can get\n");
        printf("3. Exit\n");
        printf("-------------------------------\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        printf("-------------------------------\n");

        switch (choice) {
            case 1:
                readArray();
                printf("10 activities' activity points entered into array\n");
                break;
            
            case 2:
                int maxActivityPoints = calculateMax();
                printf("Maximum number of activity points you can earn: %d\n", maxActivityPoints);
                break;

            case 3:
                printf("Exiting program...\n");
                printf("-------------------------------\n");
                exit(0);

            default:
                printf("Invalid choice, please enter a choice from (1-3) only!\n");
        }
    }
}