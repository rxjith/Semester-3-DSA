// Name: Rojith Jinenth Varghese
// Class: CSE-B 2025-2029

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int coef;
	int expo;
} poly;

int readPoly(poly *, int, int);

int addPoly(poly *, int, poly *, int, poly *, int);

void displayPoly(poly *, int, int);

int main(void) {
	
	poly x1[20], x2[20], x3[40];
	
	printf("Welcome to my Polynomial Addition Program!\n");
	
	while (true) {
		int choice;

		printf("----------------------------------------------\n");
		printf("1. Read 2 Polynomials\n2. Display 2 Polynomials\n3. Add 2 Polynomials\n4. Display Sum\n5. Exit\n");
		printf("----------------------------------------------\n");
		printf("Please enter your choice (1/2/3/4/5): ");
		scanf("%d", &choice);
		printf("----------------------------------------------\n");
		
		switch (choice) {
			case 1:
				int t1 = readPoly(x1, t1, 1);
				printf("----------------------------------------------\n");
				int t2 = readPoly(x2, t2, 2);
				int t3 = 0;
				break;
			case 2: 
				displayPoly(x1, t1, 1);	
				displayPoly(x2, t2, 2);
				break;
			case 3: 
				t3 = addPoly(x1, t1, x2, t2, x3, t3);
				printf("Polynomials added!\n");
				break;
			case 4:
				displayPoly(x3, t3, 3);
				break;
			case 5: 
				printf("Exiting program...\n");
				return 0;
			default:
				printf("Invalid choice! Please try again!\n");
		}
	}
	
	return 0;
	
}

int readPoly(poly *x, int term, int polyNo) {
	printf("Enter number of terms in polynomial %d: ", polyNo);			// prompt user to enter # of terms
	scanf("%d", &term);
	
	printf("\n");
	for (int i = 0; i < term; i++) {
		printf("Enter coefficient of term %d: ", i + 1);				// prompt user to enter coef of ith term
		scanf("%d", &x[i].coef);									
		printf("Enter exponent of term %d: ", i + 1);					// prompt user to enter exponent of ith term
		scanf("%d", &x[i].expo);
	}

	return term;														// returns # of terms (term) to main
}

int addPoly(poly *x1, int t1, poly *x2, int t2, poly *x3, int t3) {
	int i = 0, j = 0, k = 0;
	while ((i < t1) && (j < t2)) {
		if (x1[i].expo == x2[j].expo) { 								// if both exponents are equal
			x3[k].coef = x1[i].coef + x2[j].coef;
			x3[k].expo = x1[i].expo;
			i++; j++; k++;
		} else if (x1[i].expo > x2[j].expo) {							// ith exponent > jth exponent
			x3[k].coef = x1[i].coef;
			x3[k].expo = x1[i].expo;
			i++; k++;
		} else if (x1[i].expo < x2[j].expo) {							// ith exponent < jth exponent
			x3[k].coef = x2[j].coef;
			x3[k].expo = x2[j].expo;
			j++; k++;
		}
	}
	
	while (i < t1) {													// copy left over terms
		x3[k].coef = x1[i].coef;										// if there are terms remaining in poly1
		x3[k].expo = x1[i].expo;
		i++; k++;
	}
	
	while (j < t2) {													// copy left over terms
		x3[k].coef = x2[j].coef;										// if there are terms remaining in poly2
		x3[k].expo = x2[j].expo;
		j++; k++;
	}		
	
	return k;															// returning final number of terms (k) to main
}

void displayPoly(poly *x, int noOfTerms, int polyNo) {
	
	printf("Polynomial %d: ", polyNo);
	if (noOfTerms == 0) {												// if # of terms (noOfTerms) is 0, then we print 0
		printf("0\n");
		return;															// returning void
	}
	
	for (int i = 0; i < noOfTerms; i++) {
		int c = x[i].coef;												// loading up coef of ith term for ith run
		int e = x[i].expo;												// loading up expo of ith term for ith run
		
		if (c == 0) continue;											// if the coefficient is 0, no need to print anything
		
		if (i > 0 && c > 0) {
			printf(" + ");											
		} else if (i == 0 && c < 0) {
			printf("-");
			c = -c;
		} else if (i > 0 && c < 0) {
			printf(" - ");
			c = -c;
		}
		
		if (c != 1 || e == 0) { 
			printf("%d", c);
		}
		
		if (e > 0) {
			if (e == 1) {
				printf("x");
			} else {
				printf("x^%d", e);
			}
		}
	} printf("\n");
}
