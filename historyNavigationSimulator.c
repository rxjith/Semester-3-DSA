/* Implement backward and forward navigation of visited web pages in a web
   browser (i.e. back and forward buttons) using doubly linked list operations. */

// Implementation using Doubly Linked List version of a stack.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct history {
    struct history* previous;
    struct history* next;
    char site[100];
}history;

history *head = NULL, *tail = NULL, *current = NULL;

void enterURLandVisitSite(void);
void back(void);
void forward(void);
void deleteHistoryAndExit(void);

int main(void) {

    int choice;

    while (true) {
        printf("Browser Navigation Simulator:\n");
        printf("--------------------------------\n");
        printf("1. Enter a URL\n");
        printf("2. Go back a page\n");
        printf("3. Go forward a page\n");
        printf("4. Exit\n");
        printf("--------------------------------\n");
        printf("Enter your choice (1-4): "); scanf("%d", &choice);
        printf("--------------------------------\n");

        switch (choice) {
            case 1:
                enterURLandVisitSite();
                break;
            case 2:
                back();
                break;
            case 3:
                forward();
                break;
            case 4:
                deleteHistoryAndExit();
            default:
                printf("Invalid entry, please enter a choice from 1-4 only!\n");
        }

        printf("--------------------------------\n");
    }
}

void enterURLandVisitSite() {

    char URL[100];

    printf("Enter a URL: ");
    scanf(" %99[^\n]", URL);

    history* newPage = malloc(sizeof(history) + strlen(URL) + 1);

    if (!newPage) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newPage->site, URL);
    newPage->next = NULL;

    if (head == NULL) {
        newPage->previous = NULL;
        head = tail = current = newPage;
    } else {
        tail->next = newPage;
        newPage->previous = tail;
        tail = current = newPage;
    }
    printf("Website visited: %s\n", URL);

}

void back(void) {
    if (current != NULL && current->previous != NULL) {
        current = current->previous;
        printf("Current website: %s\n", current->site);
    } else {
        printf("Cannot go back, no websites available!\n");
    }
}

void forward(void) {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        printf("Current website: %s\n", current->site);
    } else {
        printf("Cannot go forward, no websites available!\n");
    }
}

void deleteHistoryAndExit(void) {
    history* temp = tail;

    while (temp != NULL) {
        tail = temp->previous;
        free(temp);
        temp = tail;
    } printf("Browser history erased!\nExiting...\n");
    exit(0);
}