#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int arr[MAX];
int n = 0; // Number of active elements

// Instrumentation Counters
long long totalTimeCounter = 0;
long long totalSpaceCounter = 0;

long long bsTimeCounter = 0;
long long bsSpaceCounter = 0;

void initArray(void) {
    printf("Enter number of elements (1-%d): ", MAX);
    scanf("%d", &n);
    totalTimeCounter++;

    if (n <= 0 || n > MAX) {
        printf("Invalid size!\n");
        n = 0;
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
        totalTimeCounter++;
    }
    printf("Array elements inserted!\n");
}

void bubbleSort(void) {
    if (n <= 1) return;

    int temp;
    // Track 1 local swap variable allocated once (4 bytes)
    totalSpaceCounter += sizeof(int);

    for (int i = 0; i < n - 1; i++) {
        totalTimeCounter++;
        for (int j = 0; j < n - 1 - i; j++) {
            totalTimeCounter++;
            if (arr[j] > arr[j + 1]) {
                totalTimeCounter += 3; // Compare + 3 assignment ops
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Array sorted successfully!\n");
}

// Iterative Binary Search (O(1) Aux Space Complexity)
int binarySearch(int target) {
    int low = 0, high = n - 1, mid;

    // Track stack frame space for low, high, mid (3 * 4 bytes)
    bsSpaceCounter += (3 * sizeof(int));
    totalSpaceCounter += (3 * sizeof(int));

    while (low <= high) {
        bsTimeCounter++;
        totalTimeCounter++;

        mid = low + (high - low) / 2;
        bsTimeCounter++;
        totalTimeCounter++;

        if (arr[mid] == target) {
            bsTimeCounter++;
            totalTimeCounter++;
            return mid;
        } else if (arr[mid] < target) {
            bsTimeCounter += 2;
            totalTimeCounter += 2;
            low = mid + 1;
        } else {
            bsTimeCounter += 2;
            totalTimeCounter += 2;
            high = mid - 1;
        }
    }
    return -1;
}

int main(void) {
    int choice, target, result;

    // Calculate Static Global Memory Space
    // Global array + n + counters
    totalSpaceCounter += (MAX * sizeof(int)) + sizeof(int) + (4 * sizeof(long long));

    printf("Binary Search Simulator\n");

    while (1) {
        printf("\n----------------------------------------\n");
        printf("1. Enter elements into array\n");
        printf("2. Binary search\n");
        printf("3. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter choice (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initArray();
                bubbleSort();
                break;

            case 2:
                if (n == 0) {
                    printf("Array is empty! Please enter elements first.\n");
                    break;
                }
                printf("Enter target key to search: ");
                scanf("%d", &target);

                // Reset per-search BS counters
                bsTimeCounter = 0;
                bsSpaceCounter = 0;

                result = binarySearch(target);

                if (result == -1) {
                    printf("%d was NOT found in the array.\n", target);
                } else {
                    printf("%d was found at index %d (Position %d)!\n", target, result, result + 1);
                }
                break;

            case 3:
                printf("Exiting program...\n");
                printf("========================================\n");
                printf("Total Execution Metrics:\n");
                printf("  Total Ops (Time):  %lld units\n", totalTimeCounter);
                printf("  Total Alloc (Space): %lld bytes\n", totalSpaceCounter);
                printf("----------------------------------------\n");
                printf("Last Binary Search Metrics:\n");
                printf("  BS Ops (Time):     %lld units\n", bsTimeCounter);
                printf("  BS Alloc (Space):    %lld bytes\n", bsSpaceCounter);
                printf("========================================\n");
                exit(0);

            default:
                printf("Invalid option! Choose between 1-3.\n");
        }
    }
    return 0;
}
