#include <stdio.h>

#define MAX_SIZE 10

int main(void) {
    int row, col;
    
    printf("Enter number of rows of A: ");
    scanf("%d", &row);
    printf("Enter number of columns of A: ");
    scanf("%d", &col);

    if (row > MAX_SIZE || col > MAX_SIZE) {
        printf("Error: Maximum size allowed is %dx%d\n", MAX_SIZE, MAX_SIZE);
        return 1;
    }

    int A[MAX_SIZE][MAX_SIZE];
    int effA[25][3]; 
    
    int k = 1; 

    // Reading elements into Matrix A
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            printf("Enter element into row %d, col %d: ", r, c);
            scanf("%d", &A[r][c]);
            
            if (A[r][c] != 0) {
                effA[k][0] = r;       // Store the Row index
                effA[k][1] = c;       // Store the Column index
                effA[k][2] = A[r][c]; // Store the actual Value
                k++;                  // Move to the next slot
            }
        }
    }

    effA[0][0] = row;     // Total rows of A
    effA[0][1] = col;     // Total columns of A
    effA[0][2] = k - 1;   // Total non-zero elements (k started at 1, so subtract 1)

    printf("\nOriginal Matrix A:\n");
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            printf("%d\t", A[r][c]);
        } printf("\n");
    }

    printf("\nEffective Matrix (Sparse Representation):\n");
    printf("---------------------\n");

    printf("%d\t%d\t%d\t\n", effA[0][0], effA[0][1], effA[0][2]);
    for (int r = 1; r < k; r++) {
        for (int c = 0; c < 3; c++) {
            printf("%d\t", effA[r][c]);
        } printf("\n");
    }

    // Transpose of a sparse matrix coming soon :D
    return 0;
}