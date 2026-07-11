#include <stdio.h>
#include <stdlib.h>

// Function Declarations
void readMatrix(int row, int col, int (*matrix)[col]);
int nonZeroCounter(int row, int col, int (*matrix)[col]);
void makeEffective(int row, int col, int nz, int (*matrix)[col], int (*effMatrix)[3]);
int add_effMatrix(int (*effA)[3], int (*effB)[3], int (*effSum)[3]);
void transpose_matrix(int row, int col, int (*matrix)[col], int (*trans_matrix)[row]);
void transpose_effMatrix(int (*effMatrix)[3], int (*trans_effMatrix)[3]);
void displayMatrix(int row, int col, int (*matrix)[col]);

int main(void) {
    int rowA, colA, rowB, colB;

    printf("Sparse Matrix Addition & Transpose (3-Tuple Representation)\n");
    printf("-----------------------------------------------------------\n");
    printf("Enter number of rows of [A]: "); scanf("%d", &rowA);
    printf("Enter number of columns of [A]: "); scanf("%d", &colA);
    printf("-----------------------------------------------------------\n");
    printf("Enter number of rows of [B]: "); scanf("%d", &rowB);
    printf("Enter number of columns of [B]: "); scanf("%d", &colB);
    printf("-----------------------------------------------------------\n");

    // Check if matrix addition is valid
    if (rowA != rowB || colA != colB) {
        printf("Error: Matrix addition requires [A] and [B] to have identical dimensions!\n");
        return 1;
    }

    int (*matrixA)[colA] = malloc(rowA * sizeof(*matrixA));
    int (*matrixB)[colB] = malloc(rowB * sizeof(*matrixB));

    if (matrixA == NULL || matrixB == NULL) {
        printf("Memory allocation failed for dense input matrices!\n");
        return 1;
    }

    printf("\nEnter elements for Matrix [A]:\n");
    readMatrix(rowA, colA, matrixA);
    printf("\nEnter elements for Matrix [B]:\n");
    readMatrix(rowB, colB, matrixB);

    int nzA = nonZeroCounter(rowA, colA, matrixA);
    int nzB = nonZeroCounter(rowB, colB, matrixB);

    // Allocate memory for 3-tuple triplet representations (+1 for header row)
    int (*effA)[3] = malloc((nzA + 1) * sizeof(*effA));
    int (*effB)[3] = malloc((nzB + 1) * sizeof(*effB));
    
    // Sum triplet matrix can have at most (nzA + nzB) non-zero terms
    int (*effSum)[3] = malloc((nzA + nzB + 1) * sizeof(*effSum));

    if (effA == NULL || effB == NULL || effSum == NULL) {
        printf("Memory allocation failed for 3-tuple matrices!\n");
        return 1;
    }

    makeEffective(rowA, colA, nzA, matrixA, effA);
    makeEffective(rowB, colB, nzB, matrixB, effB);

    printf("\n-----------------------------------------------------------\n");
    printf("3-Tuple Representation of Matrix [A]:\n");
    displayMatrix(nzA + 1, 3, effA);

    printf("\n3-Tuple Representation of Matrix [B]:\n");
    displayMatrix(nzB + 1, 3, effB);

    // Perform Addition using 3-Tuple representations
    int nzSum = add_effMatrix(effA, effB, effSum);

    printf("\n-----------------------------------------------------------\n");
    printf("3-Tuple Representation of Sum ([A] + [B]):\n");
    displayMatrix(nzSum + 1, 3, effSum);

    // Allocate transposed 3-tuple matrix
    int (*trans_effSum)[3] = malloc((nzSum + 1) * sizeof(*trans_effSum));
    
    if (trans_effSum == NULL) {
        printf("Memory allocation failed for transposed 3-tuple sum matrix!\n");
        return 1;
    }

    // Transpose the 3-Tuple Sum matrix
    transpose_effMatrix(effSum, trans_effSum);

    printf("\n-----------------------------------------------------------\n");
    printf("3-Tuple Representation of Transposed Sum ([A] + [B])^T:\n");
    displayMatrix(nzSum + 1, 3, trans_effSum);
    printf("-----------------------------------------------------------\n");

    // Clean up memory
    free(matrixA); free(matrixB);
    free(effA); free(effB);
    free(effSum); free(trans_effSum);

    return 0;
}

// Reads values into dense matrix
void readMatrix(int row, int col, int (*matrix)[col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Completed standard fallback transposition for dense elements
void transpose_matrix(int row, int col, int (*matrix)[col], int (*trans_matrix)[row]) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            trans_matrix[c][r] = matrix[r][c];
        }
    }
}

// Counts non-zero elements
int nonZeroCounter(int row, int col, int (*matrix)[col]) {
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] != 0) count++;
        }
    }
    return count;
}

// Creates 3-Tuple representation (Row 0 contains [Total Rows, Total Cols, Total Non-Zero])
void makeEffective(int row, int col, int nz, int (*matrix)[col], int (*effMatrix)[3]) {
    effMatrix[0][0] = row;
    effMatrix[0][1] = col;
    effMatrix[0][2] = nz;

    int k = 1;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] != 0) {
                effMatrix[k][0] = i;
                effMatrix[k][1] = j;
                effMatrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }
}

// Adds two 3-tuple sparse matrices and returns the number of non-zero entries in the sum
int add_effMatrix(int (*effA)[3], int (*effB)[3], int (*effSum)[3]) {
    int i = 1, j = 1, k = 1;
    int nzA = effA[0][2];
    int nzB = effB[0][2];

    effSum[0][0] = effA[0][0];
    effSum[0][1] = effA[0][1];

    while (i <= nzA && j <= nzB) {
        // Compare row indices first
        if (effA[i][0] < effB[j][0]) {
            effSum[k][0] = effA[i][0];
            effSum[k][1] = effA[i][1];
            effSum[k][2] = effA[i][2];
            i++; 
            k++;
        } 
        else if (effA[i][0] > effB[j][0]) {
            effSum[k][0] = effB[j][0];
            effSum[k][1] = effB[j][1];
            effSum[k][2] = effB[j][2];
            j++; 
            k++;
        } 
        else {
            // Rows are equal, compare column Indices
            if (effA[i][1] < effB[j][1]) {
                effSum[k][0] = effA[i][0];
                effSum[k][1] = effA[i][1];
                effSum[k][2] = effA[i][2];
                i++; 
                k++;
            } 
            else if (effA[i][1] > effB[j][1]) {
                effSum[k][0] = effB[j][0];
                effSum[k][1] = effB[j][1];
                effSum[k][2] = effB[j][2];
                j++; 
                k++;
            } 
            else {
                // Indices match -> add non-zero values
                int sumVal = effA[i][2] + effB[j][2];
                if (sumVal != 0) { // Keep only non-zero sum entries
                    effSum[k][0] = effA[i][0];
                    effSum[k][1] = effA[i][1];
                    effSum[k][2] = sumVal;
                    k++;
                }
                i++; 
                j++;
            }
        }
    }

    // Append remaining terms of Matrix A
    while (i <= nzA) {
        effSum[k][0] = effA[i][0];
        effSum[k][1] = effA[i][1];
        effSum[k][2] = effA[i][2];
        i++; 
        k++;
    }

    // Append remaining terms of Matrix B
    while (j <= nzB) {
        effSum[k][0] = effB[j][0];
        effSum[k][1] = effB[j][1];
        effSum[k][2] = effB[j][2];
        j++; 
        k++;
    }

    int totalNonZeroSum = k - 1;
    effSum[0][2] = totalNonZeroSum;

    return totalNonZeroSum;
}

// Transposes a 3-tuple representation in O(Cols * NonZero) time
void transpose_effMatrix(int (*effMatrix)[3], int (*trans_effMatrix)[3]) {
    int numRows = effMatrix[0][0];
    int numCols = effMatrix[0][1];
    int numValues = effMatrix[0][2];

    trans_effMatrix[0][0] = numCols; // Transposed Row Count
    trans_effMatrix[0][1] = numRows; // Transposed Col Count
    trans_effMatrix[0][2] = numValues;

    if (numValues > 0) {
        int k = 1;
        // Process column by column to maintain row sorting in the transposed output
        for (int c = 0; c < numCols; c++) {
            for (int i = 1; i <= numValues; i++) {
                if (effMatrix[i][1] == c) {
                    trans_effMatrix[k][0] = effMatrix[i][1]; // Transposed Row = Old Col
                    trans_effMatrix[k][1] = effMatrix[i][0]; // Transposed Col = Old Row
                    trans_effMatrix[k][2] = effMatrix[i][2]; // Value
                    k++;
                }
            }
        }
    }
}

// Displays 2D matrix
void displayMatrix(int row, int col, int (*matrix)[col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}