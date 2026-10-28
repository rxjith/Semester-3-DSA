/* Explanation:
 * Quick sort works with the help of a helper function that
 * partitions the main array into sub-arrays around a pivot
 * element following the divide-and-conquer paradigm.
 *
 * The quickSort function is called from the main function
 * allowing it to run from the 0th to (MAX - 1)th index.
 * The quickSort function runs only if p is lesser (<) than r.
 * If that condition is satisfied, then it partitions the
 * (sub-)array into smaller parts and returns the position of
 * that (sub-)array's pivot. Which tells us two things,
 *      - The sub array to the left contains elements that are
 *        smaller than the pivot
 *      - The sub array to the right contains elements that are
 *        larger than the pivot.
 * Then each of these subarrays are recursively sorted in this way,
 * around the pivot element of that particular (sub-)array.
 */

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

int partition(int p, int r) {
    int pivot = arr[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (arr[j] < pivot) {
            int temp = arr[++i];
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

void display(void) {
    printf("Sorted arr: ");
    for (int i = 0; i < MAX; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int main(void) {
    int choice;

    printf("Quick Sort Implementation:\n");
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
                quickSort(0, MAX - 1);
                display();
                break;
            case 3:
                return 0;
            default: printf("Invalid choice, please choose between 1-3 only!\n");
        }
    }
}
