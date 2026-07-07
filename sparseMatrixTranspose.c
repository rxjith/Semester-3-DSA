#include <stdio.h>
#include <stdlib.h>

void readMatrix(int, int col, int (*matrix)[col]);
int nonZeroCounter(int row, int col, int (*matrix)[col]);
void makeEffective(int row, int col, int nz, int (*matrix)[col], int (*effMatrix)[3]);
void transpose(int row, int col, int (*matrix)[col], int (*transposedMatrix)[row]);
void transpose_effMatrix(int (*effMatrix)[3], int (*trans_effMatrix)[3]);
void displayMatrix(int row, int col, int (*matrix)[col]);

int main(void) {
    int row, col;
    printf("Sparse Matrix Transpose Calculator:\n");
    printf("--------------------------------------\n");
    printf("Enter number of rows of [A]: "); scanf("%d", &row);
    printf("Enter number of columns of [A]: "); scanf("%d", &col);
    printf("--------------------------------------\n");

    int (*matrix)[col] = malloc(row * sizeof(*matrix));

    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    readMatrix(row, col, matrix);
    printf("--------------------------------------\n");
    printf("[Matrix]:\n");
    displayMatrix(row, col, matrix);
    printf("--------------------------------------\n");

    int nz = nonZeroCounter(row, col, matrix);
    int (*effMatrix)[3] = malloc((nz + 1) * sizeof(*effMatrix)); 

    if (effMatrix == NULL) {
        printf("Memory allocation failed (Effective Representation of Matrix)!\n");
        return 1;
    }

    int (*transposedMatrix)[row] = malloc(row * sizeof(*transposedMatrix));

    if (transposedMatrix == NULL) {
        printf("Memory allocation failed (Transposed Matrix)!\n");
        return 1;
    }

    int (*trans_effMatrix)[3] = malloc((nz + 1) * sizeof(*trans_effMatrix));

    if (trans_effMatrix == NULL) {
        printf("Memory allocation failed (Effective Representation of Transposed Matrix)!\n");
        return 1;
    }

    makeEffective(row, col, nz, matrix, effMatrix);
    printf("--------------------------------------\n");

    printf("Effective Representation of the entered Sparse Matrix:\n");
    displayMatrix(nz + 1, 3, effMatrix);
    printf("--------------------------------------\n");

    printf("Transposing...\n");
    transpose_effMatrix(effMatrix, trans_effMatrix);
    printf("--------------------------------------\n");

    printf("Transposed Matrix:\n");
    transpose(row, col, matrix, transposedMatrix);
    displayMatrix(col, row, transposedMatrix);
    printf("--------------------------------------\n");

    printf("Effective Representation of the transposed Sparse Matrix:\n");
    displayMatrix(nz + 1, 3, trans_effMatrix);
    printf("--------------------------------------\n");

    free(matrix), free(effMatrix), free(transposedMatrix), free(trans_effMatrix);
}

void readMatrix(int row, int col, int (*matrix)[col]) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            printf("Enter element into row %d, col %d: ", r, c);
            scanf("%d", &matrix[r][c]);
        }
    }
}

int nonZeroCounter(int row, int col, int (*matrix)[col]) {
    int nz = 0;
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (matrix[r][c] != 0) nz++;
        }
    }
    
    return nz;
}

void makeEffective(int row, int col, int nz, int (*matrix)[col], int (*effMatrix)[3]) {
    for (int r = 0, k = 1; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (matrix[r][c] != 0) {
                effMatrix[k][0] = r;
                effMatrix[k][1] = c;
                effMatrix[k][2] = matrix[r][c];
                k++;
            }
        }
    }
    effMatrix[0][0] = row, effMatrix[0][1] = col, effMatrix[0][2] = nz;
    printf("Effective representation was generated!\n");
}

void transpose(int row, int col, int (*matrix)[col], int (*transposedMatrix)[row]){
    for (int r = 0; r < col; r++) {
        for (int c = 0; c < row; c++) {
            transposedMatrix[r][c] = matrix[c][r]; 
        }
    }
}

void transpose_effMatrix(int (*effMatrix)[3], int (*trans_effMatrix)[3]) {
    int rows = effMatrix[0][0];
    int cols = effMatrix[0][1];
    int nz   = effMatrix[0][2];

    // Header
    trans_effMatrix[0][0] = cols;
    trans_effMatrix[0][1] = rows;
    trans_effMatrix[0][2] = nz;

    int k = 1;

    // For every column of the original matrix
    for (int c = 0; c < cols; c++) {

        // Scan every non-zero element
        for (int i = 1; i <= nz; i++) {

            if (effMatrix[i][1] == c) {
                trans_effMatrix[k][0] = effMatrix[i][1];
                trans_effMatrix[k][1] = effMatrix[i][0];
                trans_effMatrix[k][2] = effMatrix[i][2];
                k++;
            }
        }
    }
}

void displayMatrix(int row, int col, int (*matrix)[col]) {
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            printf("%d\t", matrix[r][c]);
        } printf("\n");
    }
}