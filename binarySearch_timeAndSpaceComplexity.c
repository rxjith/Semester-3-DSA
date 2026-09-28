#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int arr[MAX] = {0}, n = 0;

int initArray(void) {
    for (int i = 0; i < MAX; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
        n++;
    }
    printf("Array elements inserted!\n");
}

/*
int linearSearch(int target) {
    for (int i = 0; i < MAX; i++) {
        if (target == arr[i]) {
            return i;
        }
    } return -1;
} 
*/

int low = 0, high = MAX - 1;

void bubbleSort(void) {
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    
    printf("Array sorted!\n");
}

int binarySearch(int target, int low, int high) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (target == arr[mid]) return mid;
    else if (target < arr[mid]) return binarySearch(target, low, mid - 1);
    else return binarySearch(target, mid + 1, high);
}

int main(void) {
    int choice, target, result;
    
    printf("Binary Search Implementation:\n");

    while (1) {
        printf("----------------------------------------\n");
        printf("1. Enter elements into array\n");
        printf("2. Binary search\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        printf("----------------------------------------\n");

        switch (choice) {
            case 1:
                initArray();
                break;
            case 2:
                if (n != 0) {
                    bubbleSort();
                    printf("----------------------------------------\n");
                    printf("Enter target to search for: ");
                    scanf("%d", &target);
                    printf("----------------------------------------\n");
                    result = binarySearch(target, low, high);
                    if (result == -1) {
                        printf("%d was not found in the given array!\n", target);
                    } else {
                        printf("%d was found at position %d!\n", target, result + 1);
                    }
                }
                else printf("Array is empty! Cannot perform binary search!\n");
                break;
            case 3:
                printf("Exiting program...\n");
                printf("----------------------------------------\n");
                exit(0);
            default:
                printf("Invalid choice, please enter a choice from 1-3 only!\n");
        }
    }
}