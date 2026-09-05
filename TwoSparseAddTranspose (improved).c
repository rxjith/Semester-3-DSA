// Find the sum of two sparse matrices and transpose the resultant matrix.

#include <stdio.h>
#include <stdlib.h>

int *M1 = NULL, *M2 = NULL, *SUM = NULL;
int row1 = 0, col1 = 0, row2 = 0, col2 = 0, rowSUM = 0, colSUM = 0;

int NZE = 0;

int* effSUM = NULL;
int row_effSUM = 0, col_effSUM = 3;

int* trans_effSUM = NULL;
int row_trans_effSUM = 0, col_trans_effSUM = 3;

void readSparse(void);
void displaySparse(int*, int, int);
void addSparse(int*, int, int, int*);
void nonZeroCounter(void);
void effectiveize(void);
void displayEffective(int*, int);
void effectiveTranspose(void);

int main(void) {

    int choice;
    
    printf("Two Sparse Sum & Transpose Program:\n");

    while (1) {
        
        printf("---------------------------------------------\n");
        printf("1. Read 2 Sparse Matrices\n2. Add 2 Sparse Matrices\n3. Transpose Resultant Matrix\n4. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice (1-4): "); scanf("%d", &choice);
        printf("---------------------------------------------\n");

        switch (choice) {
            case 1:
                readSparse();
                printf("Matrix 1:\n"); displaySparse(M1, row1, col1);
                printf("\n");
                printf("Matrix 2:\n"); displaySparse(M2, row2, col2);
                break;
            case 2:
                addSparse(M1, row1, col1, M2);
                printf("Dense Sum Matrix:\n");
                displaySparse(SUM, rowSUM, colSUM);
                effectiveize();
                printf("\n3-Tuple Matrix (SUM):\n");
                displayEffective(effSUM, row_effSUM);
                break;
            case 3:
                effectiveTranspose();
                printf("3-Tuple Matrix Transposed:\n");
                displayEffective(trans_effSUM, row_trans_effSUM);
                break;
            case 4:
                free(M1); free(M2); free(SUM);
                free(effSUM); free(trans_effSUM);
                exit(0);
            default: printf("Invalid choice, please pick from 1-4 only!\n");
        }
    }
}
    
void readSparse(void) {

    printf("Enter number of rows in Matrix 1: "); scanf("%d", &row1);
    printf("Enter number of columns in Matrix 1: "); scanf("%d", &col1);
    printf("---------------------------------------------\n");
    printf("Enter number of rows in Matrix 2: "); scanf("%d", &row2);
    printf("Enter number of columns in Matrix 2: "); scanf("%d", &col2);

    if (row1 != row2 || col1 != col2) {
        printf("Error: Dimensions of matrices have to be the same!\n");
        return;
    }

    rowSUM = row1; colSUM = col1;

    if (M1) free(M1);
    if (M2) free(M2);
    if (SUM) free(SUM);

    M1 = malloc(row1 * col1 * sizeof(int));
    M2 = malloc(row2 * col2 * sizeof(int));
    SUM = malloc(rowSUM * colSUM * sizeof(int));

    if (!M1 || !M2 || !SUM) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("---------------------------------------------\n");
    printf("Enter Matrix 1 Elements:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            printf("Enter element [%d][%d]: ", i + 1, j + 1); scanf("%d", &M1[i * col1 + j]);
        }
    }
    printf("---------------------------------------------\n");
    printf("Enter Matrix 2 Elements:\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            printf("Enter element [%d][%d]: ", i + 1, j + 1); scanf("%d", &M2[i * col2 + j]);
        }
    }
    printf("---------------------------------------------\n");
}

void displaySparse(int* matrix, int row, int col) {
    if (!matrix) return;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i * col + j]); 
        } printf("\n");
    }
}

void addSparse(int* m1, int row1, int col1, int* m2) {
    if (!SUM) return;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            SUM[i * col1 + j] = m1[i * col1 + j] + m2[i * col1 + j];
        }
    }
}

void nonZeroCounter(void) {
    if (!SUM) {
        NZE = 0;
        return;
    }

    NZE = 0;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            if (SUM[i * col1 + j] != 0) NZE++;
        }
    }
}

void effectiveize(void) {
    if (!SUM) return;

    nonZeroCounter();
    row_effSUM = NZE;

    if (effSUM) free(effSUM);

    effSUM = malloc((NZE + 1) * 3 * sizeof(int));

    effSUM[0 * 3 + 0] = rowSUM; 
    effSUM[0 * 3 + 1] = colSUM;
    effSUM[0 * 3 + 2] = NZE;
    
    int k = 1;
    for (int i = 0; i < rowSUM; i++) {
        for (int j = 0; j < colSUM; j++) {
            if (SUM[i * colSUM + j] != 0) {
                effSUM[k * 3 + 0] = i;
                effSUM[k * 3 + 1] = j;
                effSUM[k * 3 + 2] = SUM[i * colSUM + j];
                k++; 
            }
        }
    }
}

void displayEffective(int *matrix, int rows) {
    if (!matrix) return;
    printf("Row\tCol\tVal\n");
    printf("-------------------\n");
    for (int i = 0; i <= rows; i++) {
        printf("%d\t%d\t%d\n", matrix[i * 3 + 0], matrix[i * 3 + 1], matrix[i * 3 + 2]);
    }
}

void effectiveTranspose(void) {
    if (!effSUM) return;

    NZE = effSUM[0 * 3 + 2];
    row_trans_effSUM = NZE;

    if (trans_effSUM) free(trans_effSUM);
    trans_effSUM = malloc((NZE + 1) * 3 * sizeof(int));

    trans_effSUM[0 * 3 + 0] = effSUM[0 * 3 + 1];
    trans_effSUM[0 * 3 + 1] = effSUM[0 * 3 + 0];
    trans_effSUM[0 * 3 + 2] = NZE;

    int k = 1;
    for (int col = 0; col < effSUM[0 * 3 + 1]; col++) {
        for (int i = 1; i <= NZE; i++) {
            if (effSUM[i * 3 + 1] == col) {
                trans_effSUM[k * 3 + 0] = effSUM[i * 3 + 1];
                trans_effSUM[k * 3 + 1] = effSUM[i * 3 + 0];
                trans_effSUM[k * 3 + 2] = effSUM[i * 3 + 2];
                k++;
            }
        }
    }
}