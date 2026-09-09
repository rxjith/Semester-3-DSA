#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    } if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    } return root;
}

int search(Node* root, int val) {
    if (root == NULL) return 0;
    if (root->data == val) return 1;
    return (val < root->data) ? search(root->left, val) : search(root->right, val);
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) root = root->left;
    return root;
}

int height(Node* root) {
    if (root == NULL) return 0;
    int leftH = height(root->left);
    int rightH = height(root->right);
    return 1 + (leftH > rightH ? leftH : rightH);
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) return root;

    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->data) {
        root->right = deleteNode(root->right, val); 
    } else {
        if (root->left == NULL) { // Case 1 & 2: 0 or 1 child
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: 2 children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    Node* root = NULL;
    int choice, val;

    do {
        printf("----------------------------------------------\n");
        printf("1. Insert\n2. Display (InOrder)\n3. Search\n4. Height\n5. Delete\n6. Exit\n");
        printf("----------------------------------------------\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        printf("----------------------------------------------\n");
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                printf("%d inserted!\n", val);
                break;
            
            case 2:
                inOrder(root);
                printf("\n");
                break;

            case 3:
                printf("Enter value to search for: ");
                scanf("%d", &val);
                int isFound = search(root, val);
                printf("%s\n", isFound ? "Found!" : "Not found!");
                break;

            case 4:
                printf("Height of Binary Search Tree: %d Levels\n", height(root));
                break;

            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                root = deleteNode(root, val);
                printf("%d deleted!\n", val);
                break;

            case 6:
                printf("Freeing memory and exiting program...\n");
                printf("----------------------------------------------\n");
                freeTree(root);
                root = NULL;
                break;

            default:
                printf("Invalid choice, please choose between 1-6!\n");
        }
    } while (choice != 6);
    return 0;
}