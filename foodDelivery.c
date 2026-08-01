/* A food delivery platform maintains the list of active orders. 
 * New orders are continuously added, and completed orders are removed. */

// Rojith Jinenth Varghese
// CSE-B 2025-2029

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define ITEM_NAME_MAX 30

typedef struct Order {
    int orderID;
    int noOfItems;
    char* items[MAX];
    struct Order *next;
} Order;

Order *front = NULL, *rear = NULL;

void createOrder(void);
void fulfillOrder(int orderID);
void printOrders(void);
void searchOrders(int orderID);
void freeOrders(void);

int main(void) {

    int choice, orderID;
    printf("Food Delivery Platform (v1.0.0):\n");
    while (true) {
        printf("------------------------------------\n");
        printf("1. Place new order\n2. Mark an order as fulfilled\n3. Print orders\n4. Search for an order\n5. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1/2/3/4/5): ");
        if (scanf("%d", &choice) != 1) break;
        printf("------------------------------------\n");

        switch (choice) {
            case 1:
                createOrder();
                break;
            
            case 2:
                printf("Enter orderID of the order that has been fulfilled: ");
                scanf("%d", &orderID);
                fulfillOrder(orderID);
                break;
            
            case 3:
                printOrders();
                break;

            case 4:
                printf("Enter orderID of order you want to search for: ");
                scanf("%d", &orderID);
                searchOrders(orderID);
                break;
            
            case 5:
                freeOrders();
                exit(0);
            
            default:
                printf("Invalid input, please try again!\n");
        }
    }
}

void createOrder(void) {
    Order* newOrder = malloc(sizeof(Order));

    if (!newOrder) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter orderID: ");
    scanf("%d", &newOrder->orderID);

    printf("Enter number of items (<=10 only): ");
    scanf("%d", &newOrder->noOfItems);

    if (newOrder->noOfItems <=0 || newOrder->noOfItems > MAX) {
        printf("INVALID SIZE! ENTER 1 TO 10 ITEMS ONLY!\n");
        free(newOrder);
        return;
    }

    for (int i = 0; i < newOrder->noOfItems; i++) {
        newOrder->items[i] = malloc(ITEM_NAME_MAX * sizeof(char));
        printf("Enter item %d: ", i + 1);
        scanf(" %29[^\n]", newOrder->items[i]);
    }

    newOrder->next = NULL;

    if (front == NULL) {
        front = rear = newOrder;
    } else {
        rear->next = newOrder;
        rear = newOrder;
    }

    printf("Order #%d has been placed successfully!\n", newOrder->orderID);
    return;
}

void fulfillOrder(int orderID) {
    if (front == NULL) {
        printf("No orders to fulfill!\n");
        return;
    }

    Order *current = front;
    Order *prev = NULL;

    while (current != NULL && current->orderID != orderID) {
        prev = current;
        current = current->next; 
    }

    if (current == NULL) {
        printf("Order ID %d not found in the queue!\n", orderID);
        return;
    }

    if (current == front) {
        front = front->next;
        if (front == NULL) rear = NULL;
    } else {
        prev->next = current->next;
        if (current == rear) rear = prev;
    }

    for (int i = 0; i < current->noOfItems; i++) {
        free(current->items[i]);
    }

    free(current);
    printf("Order %d fulfilled successfully!\n", orderID);
}

void printOrders(void) {
    if (front == NULL) {
        printf("No orders to show here!\n");
        return;
    }
    
    Order *current = front;
    
    printf("ACTIVE ORDERS:\n");
    while (current != NULL) {
        printf("------------------------------------\n");
        printf("OrderID: %d\n\n", current->orderID);
        printf("Items:\n");
        for (int i = 0; i < current->noOfItems; i++) {
            printf("  %d. %s\n", i + 1, current->items[i]);
        }
        current = current->next;
    }
}

void searchOrders(int orderID) {
    if (front == NULL) {
        printf("No orders exist!\n");
        return;
    }

    Order *current = front;

    while (current != NULL) {
        if (current->orderID == orderID) {
            printf("\n--- ORDER FOUND ---\n");
            printf("OrderID: %d\n", current->orderID);
            printf("Items:\n");
            for (int i = 0; i < current->noOfItems; i++) {
                printf("  %d. %s\n", i + 1, current->items[i]);
            }
            return;
        }
        current = current->next;
    }

    printf("Order ID %d not found!\n", orderID);
}

void freeOrders(void) {
    Order *current = front;
    
    while (current != NULL) {
        Order *temp = current;
        current = current->next;

        for (int i = 0; i < temp->noOfItems; i++) {
            free(temp->items[i]);
        }
        free(temp);
    }

    front = rear = NULL;
    printf("Orders have been cleared!\n");
    return;
}