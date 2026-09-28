#include <stdio.h>
#include <stdlib.h>

int spaceComplexityCounter = 0; 

#define MAX 10
int arr[MAX] = {0}, n = 0;
int timeComplexityCounter = 0;


void initArray(void) {
    for (int i = 0; i < MAX; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
        n++;
        timeComplexityCounter++;
        spaceComplexityCounter += (1 * 4);
    }
    timeComplexityCounter++;
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
        timeComplexityCounter += (1);
        for (int j = 0; j < MAX - 1 - i; j++) {
            timeComplexityCounter += (1);
            if (arr[j] > arr[j + 1]) {
                timeComplexityCounter += (1);
                int temp = arr[j + 1]; timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);
                arr[j + 1] = arr[j]; timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);
                arr[j] = temp; timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);
            }
        } timeComplexityCounter += (1);
    } timeComplexityCounter += (1);
    printf("Array sorted!\n");
}

int binarySearch(int target, int low, int high) {
    if (low > high) {
        return -1;
    } timeComplexityCounter += (1);

    int mid = low + (high - low) / 2; timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);
    
    timeComplexityCounter += (1);
    if (target == arr[mid]) {
        return mid;

    }
    else if (target < arr[mid]) {
        return binarySearch(target, low, mid - 1);
    }
    else {
        return binarySearch(target, mid + 1, high);
    }
}

int main(void) {
    timeComplexityCounter += (3);
    spaceComplexityCounter += (4 + 4 + MAX*4);

    // for low and high:
    timeComplexityCounter += (2);
    spaceComplexityCounter += (2 * 4);

    int choice, target, result;
    timeComplexityCounter += (3);
    spaceComplexityCounter += (3 * 4);

    printf("Binary Search Implementation:\n");

    while (1) {
        timeComplexityCounter += (1);
        printf("----------------------------------------\n");
        printf("1. Enter elements into array\n");
        printf("2. Binary search\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        timeComplexityCounter += 1;
        spaceComplexityCounter += (4);
        printf("----------------------------------------\n");

        switch (choice) {
            case 1:
                initArray();
                timeComplexityCounter += (1);
                spaceComplexityCounter += (1);
                break;
            case 2:
                timeComplexityCounter += (1);
                if (n != 0) {
                    bubbleSort(); timeComplexityCounter += (1); spaceComplexityCounter += (1);
                    printf("----------------------------------------\n");
                    printf("Enter target to search for: ");
                    scanf("%d", &target); timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);
                    printf("----------------------------------------\n");
                    result = binarySearch(target, low, high);
                    timeComplexityCounter += (1); spaceComplexityCounter += (1 * 4);

                    timeComplexityCounter += (1); spaceComplexityCounter += (1);
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
                printf("Time Complexity (in units): %d\n", timeComplexityCounter);
                printf("Space Complexity (in bytes): %d\n", spaceComplexityCounter);
                exit(0);
            default:
                printf("Invalid choice, please enter a choice from 1-3 only!\n");
        }
    } timeComplexityCounter += (1); spaceComplexityCounter += (1);
}