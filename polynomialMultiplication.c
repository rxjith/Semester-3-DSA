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

int multiplyPoly(poly *, int, poly *, int, poly *, int);

void displayPoly(poly *, int, int);

int main(void) {
	
	poly x1[20], x2[20], x3[40];
	int choice, t1 = 0, t2 = 0, t3 = 0;

	printf("Welcome to my Polynomial Addition Program!\n");
	
	while (true) {

		printf("----------------------------------------------\n");
		printf("1. Read 2 Polynomials\n2. Display 2 Polynomials\n3. Multiply 2 Polynomials\n4. Display Product\n5. Exit\n");
		printf("----------------------------------------------\n");
		printf("Please enter your choice (1/2/3/4/5): ");
		scanf("%d", &choice);
		printf("----------------------------------------------\n");
		
		switch (choice) {
			case 1:
				t1 = readPoly(x1, t1, 1);
				printf("----------------------------------------------\n");
				t2 = readPoly(x2, t2, 2);
				t3 = 0;
				break;
			case 2: 
				displayPoly(x1, t1, 1);	
				displayPoly(x2, t2, 2);
				break;
			case 3: 
				t3 = multiplyPoly(x1, t1, x2, t2, x3, t3);
				printf("Polynomials multiplied and simplified!\n");
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
	printf("Enter number of terms in polynomial %d: ", polyNo);
	scanf("%d", &term);									// prompt user to enter number of terms for the polynomial
	
	printf("\n");
	for (int i = 0; i < term; i++) {
		printf("Enter coefficient of term %d: ", i+1);
		scanf("%d", &x[i].coef);						// prompt user to enter coefficient of the 'i'th term
		printf("Enter exponent of term %d: ", i+1);
		scanf("%d", &x[i].expo);						// prompt user to enter exponent of the 'i'th term
	}

	return term;
}

int multiplyPoly(poly *x1, int t1, poly *x2, int t2, poly *x3, int t3) {
	int k = 0;
	
	// Basic cross-multiplication
	for (int i = 0; i < t1; i++) {
		int c1 = x1[i].coef;
		int e1 = x1[i].expo;
		
		for (int j = 0; j < t2; j++) {
			int c2 = x2[j].coef;
			int e2 = x2[j].expo;
			
			x3[k].coef = c1 * c2;						// Multiplying coefficients
			x3[k].expo = e1 + e2;						// Adding the powers / exponents
			k++;
		}
	}
	int totalTerms = k;

	// Sort by exponent (descending order - bubble sort)
	for (int i = 0; i < totalTerms - 1; i++) {
		for (int j = 0; j < totalTerms - i - 1; j++) {
			if (x3[j].expo < x3[j+1].expo) {
				poly temp = x3[j];						// temporary placeholder variable
				x3[j] = x3[j+1];
				x3[j+1] = temp;
			}
		}
	}

	// Combine like terms in-place
	if (totalTerms == 0) return 0;
	
	int unique_count = 0; 								// Tracks the array position of unique simplified terms
	for (int i = 1; i < totalTerms; i++) {
		if (x3[i].expo == x3[unique_count].expo) {
			x3[unique_count].coef += x3[i].coef; 		// Exponents match, merge them (add)
		} else {
			unique_count++;
			x3[unique_count] = x3[i]; 					// New exponent found, advance index and copy over
		}
	}
	
	return unique_count + 1; 							// Return true size of product polynomial
}

void displayPoly(poly *x, int noOfTerms, int polyNo) {
	
	printf("Polynomial %d: ", polyNo);
	if (noOfTerms == 0) {
		printf("0\n");
		return;
	}
	
	bool printedAny = false; 							// Tracks if we actually drew any valid terms to screen
	for (int i = 0; i < noOfTerms; i++) {
		int c = x[i].coef;
		int e = x[i].expo;
		
		if (c == 0) continue;
		
		if (printedAny && c > 0) {
			printf(" + ");
		} else if (!printedAny && c < 0) {
			printf("-");
			c = -c;
		} else if (printedAny && c < 0) {
			printf(" - ");
			c = -c;
		}
		
		printedAny = true;								// Setting flag to true cuz we printed something
		
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
	} 
	
	if (!printedAny) {
		printf("0");
	}
	printf("\n");
}
