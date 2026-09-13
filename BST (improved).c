// Binary Search Tree Implementation:

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val) {
    Node* newNode = malloc(sizeof(Node));

    if (!newNode) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int val) {
    if (root == NULL) return createNode(val);
    
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    
    return root;
}

int search(Node* root, int val) {
    if (root == NULL) return 0;
    if (root->data == val) return 1;
    return (val < root->data) ? search(root->left, val) : search(root->right, val);
}

Node* findMin(Node* root) {
    if (root == NULL) return root;
    if (root->left == NULL) return root;
    return findMin(root->left);
}

int height(Node* root) {
    if (root == NULL) return 0;

    int leftH = height(root->left);
    int rightH = height(root->right);

    return 1 + (leftH > rightH ? leftH : rightH);
}

Node* deleteNode(Node* root, int val) {
    
    // Base Case:
    if (root == NULL) return root;

    // Searching for the node
    if (val < root->data) root->left = deleteNode(root->left, val);
    else if (val > root->data) root->right = deleteNode(root->right, val);

    // Deletion
    else {
        // 0 / 1 children
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // actual deletion (2 children)
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    // re-links nodes with their parents (higher up the call stack)
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
                printf("BST Content(s): ");
                inOrder(root);
                printf("\n");
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                int isFound = search(root, val);
                if (isFound) printf("Found!\n");
                else printf("Not found!\n");
                break;
            
            case 4:
                printf("Height of Binary Search Tree: %d levels\n", height(root));
                break;

            case 5:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                if (search(root, val)) {
                    root = deleteNode(root, val);
                    printf("%d deleted!\n", val);
                } else {
                    printf("%d was not found in the BST!\n", val);
                }
                break;

            case 6:
                printf("Freeing tree nodes and exiting program...\n");
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