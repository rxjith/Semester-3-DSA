// Find the sum of two polynomials using arrays (array of structures):

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct Poly {
    int coef, expo;
} Poly;

Poly x1[MAX], x2[MAX], x3[MAX];

void displayPoly(Poly [], int);
void readPoly(void);
void addPoly(void);

int t1 = 0, t2 = 0, t3 = 0;

int main(void) {

    int choice;

    printf("Polynomial Addition Program:\n");
    
    while (1) {
        printf("------------------------------------------------\n");
        printf("1. Read 2 Polynomials\n2. Add 2 Polynomials\n3. Exit\n");
        printf("------------------------------------------------\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        printf("------------------------------------------------\n");

        switch (choice) {
            case 1:
                readPoly();
                printf("Polynomial 1: "); displayPoly(x1, t1);
                printf("Polynomial 2: "); displayPoly(x2, t2);
                break;
            case 2:
                addPoly();
                printf("Resultant Polynomial: "); displayPoly(x3, t3);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice, please enter a choice from (1-3) ONLY!\n");
        }
    }
}

void displayPoly(Poly x[], int size) {

    if (size == 0) {
        printf("0\n");
        return;
    }

    int printedTerms = 0;

    for (int t = 0; t < size; t++) {
        int c = x[t].coef;
        int e = x[t].expo;

        if (c == 0) continue;

        if (printedTerms == 0) {
            if (c < 0) {printf("-"); c = -c;}
        } else {
            if (c < 0) {printf(" - "); c = -c;} 
            else {printf(" + ");}
        }

        if (c != 1 || e == 0) printf("%d", c);
        if (e == 1) printf("x");
        else if (e > 1) printf("x^%d", e);

        printedTerms++;
    }

    if (printedTerms == 0) printf("0");
    printf("\n");
}

void readPoly(void) {
    printf("Enter number of terms in the first polynomial: ");
    scanf("%d", &t1);

    printf("Enter number of terms in the second polynomial: ");
    scanf("%d", &t2);
    
    printf("------------------------------------------------\n");
    
    if (t1 <= 0 || t2 <= 0) {
        printf("No terms were read, please enter a valid number of terms!");
        printf("------------------------------------------------\n");
        return;
    }

    printf("Enter elements of 1st polynomial:\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < t1; i++) {
        printf("Enter coef. of term %d: ", i + 1);
        scanf("%d", &x1[i].coef);
        printf("Enter expo. of term %d: ", i + 1);
        scanf("%d", &x1[i].expo);
    }
    printf("------------------------------------------------\n");

    printf("Enter elements of 2nd polynomial:\n");
    printf("------------------------------------------------\n");
    for (int j = 0; j < t2;j++) {
        printf("Enter coef. of term %d: ", j + 1);
        scanf("%d", &x2[j].coef);
        printf("Enter expo. of term %d: ", j + 1);
        scanf("%d", &x2[j].expo);
    }
    printf("------------------------------------------------\n");
    printf("Polynomials were read successfully!\n");
    return;
}

void addPoly(void) {

    if (t1 == 0 || t2 == 0) {
        printf("Error: NO POLYNOMIALS TO ADD!\n");
        return;
    }

    int i = 0, j = 0, k = 0;

    while (i < t1 && j < t2) {
        if (x1[i].expo == x2[j].expo) {
            x3[k].coef = x1[i].coef + x2[j].coef;
            x3[k].expo = x1[i].expo;
            i++; j++; k++;
        }

        else if (x1[i].expo > x2[j].expo) {
            x3[k].coef = x1[i].coef;
            x3[k].expo = x1[i].expo;
            i++; k++;
        }

        else {
            x3[k].coef = x2[j].coef;
            x3[k].expo = x2[j].expo;
            j++; k++;
        }
    }

    while (i < t1) {
        x3[k].coef = x1[i].coef;
        x3[k].expo = x1[i].expo;
        i++; k++;
    }

    while (j < t2) {
        x3[k].coef = x2[j].coef;
        x3[k].expo = x2[j].expo;
        j++; k++;
    }
    
    t3 = k;

    return;
}