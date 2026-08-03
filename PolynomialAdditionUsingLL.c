// Polynomial Addition Using Linked Lists

// Rojith Jinenth Varghese
// S3 CSE - B | 2025 - 2029

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Poly {
    int coef;
    int expo;
    struct Poly* next;
} Poly;

Poly *x1 = NULL, *x2 = NULL, *x3 = NULL;

Poly* createPoly(int coef, int expo);
Poly* insertEnd(Poly *head, int coef, int expo);
Poly* readPoly(int polyNo);
Poly* addPoly(Poly *p1, Poly *p2);
void displayPoly(Poly *head, int polyNo);
Poly* freePoly(Poly *head);

int main(void) {
    
    printf("Polynomial Additon using Linked Lists:\n");
    
    while (true) {
        int choice;

        printf("----------------------------------------------\n");
		printf("1. Read 2 Polynomials\n2. Display 2 Polynomials\n3. Add 2 Polynomials\n4. Display Sum\n5. Exit\n");
		printf("----------------------------------------------\n");
		printf("Please enter your choice (1/2/3/4/5): ");
		if (scanf("%d", &choice) != 1) break;
		printf("----------------------------------------------\n");
		
		switch (choice) {
			case 1:
				x1 = freePoly(x1);
                x2 = freePoly(x2);
                x3 = freePoly(x3);

                x1 = readPoly(1);
                printf("----------------------------------------------\n");
                x2 = readPoly(2);
				break;

			case 2: 
				displayPoly(x1, 1);	
				displayPoly(x2, 2);
				break;

			case 3: 
				x3 = freePoly(x3);
                x3 = addPoly(x1, x2);
				printf("Polynomials added!\n");
				break;

			case 4:
				displayPoly(x3, 3);
				break;

			case 5: 
				printf("Exiting program...\n");
                x1 = freePoly(x1);
                x2 = freePoly(x2);
                x3 = freePoly(x3);
				return 0;

			default:
				printf("Invalid choice! Please try again!\n");
		}
	}
	
	return 0;
}

Poly* createPoly(int coef, int expo) {
    Poly* newPoly = malloc(sizeof(Poly));
    
    if (!newPoly) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newPoly->coef = coef;
    newPoly->expo = expo;
    newPoly->next = NULL;
    return newPoly;
}

Poly* insertEnd(Poly *head, int coef, int expo) {
    Poly* newPoly = createPoly(coef, expo);
    
    if (head == NULL) {
        return newPoly;
    }

    Poly *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newPoly;
    return head;
}

Poly* readPoly(int polyNo) {
    Poly *head = NULL;
    int terms, coef, expo;

    printf("Enter number of terms in polynomial %d: ", polyNo);
    scanf("%d", &terms);

    printf("\n");
    for (int i = 0; i < terms; i++) {
        printf("Enter coefficient of term %d: ", i + 1);
        scanf("%d", &coef);
        printf("Enter exponenet of term %d: ", polyNo);
        scanf("%d", &expo);

        head = insertEnd(head, coef, expo);
    }

    return head;
}

Poly* addPoly(Poly *p1, Poly *p2) {
    Poly *result = NULL;

    while (p1 != NULL && p2 != NULL) {
        if (p1->expo == p2->expo) {
            int sumCoef = p1->coef + p2->coef;
            if (sumCoef != 0) {
                result = insertEnd(result, sumCoef, p1->expo);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->expo > p2->expo) {
            result = insertEnd(result, p1->coef, p1->expo);
            p1 = p1->next;
        }
        else {
            result = insertEnd(result, p2->coef, p2->expo);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        result = insertEnd(result, p1->coef, p1->expo);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insertEnd(result, p2->coef, p2->expo);
        p2 = p2->next;
    }

    return result;
}

void displayPoly(Poly* head, int polyNo) {
    printf("Polynomial %d: ", polyNo);

    if (head == NULL) {
        printf("0\n");
        return;
    }

    Poly *curr = head;
    bool isFirst = true;

    while (curr != NULL) {
        int c = curr->coef;
        int e = curr->expo;

        if (c != 0) {
            if (!isFirst && c > 0) {
                printf(" + ");
            }
            else if (isFirst && c < 0) {
                printf("-");
                c = -c;
            }
            else if (!isFirst && c < 0) {
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
            isFirst = false;

        }
        curr = curr->next;
    }

    if (isFirst) {
        printf("0");
    }
    printf("\n");
}

Poly* freePoly(Poly *head) {
    Poly *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}