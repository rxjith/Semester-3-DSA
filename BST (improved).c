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
    newNode->left = NULL;
    newNode->right = NULL;
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
    return (root->data > val) ? search(root->left, val) : search (root->right, val);
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
    if (root == NULL) return NULL;

    if (val < root->data) root->left = deleteNode(root->left, val);
    else if (val > root->data) root->right = deleteNode(root->right, val);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

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

void preOrder(Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

void freeTree(Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {

    int choice, val;

    Node* root = NULL;

    printf("Binary Search Tree Demo:\n");

    do {
        printf("-----------------------------------------\n");
        printf("1. Insert a node\n2. Display (in order)\n3. Display (pre-order)\n4. Display (post-order)\n5. Search for a node\n6. Height of BST\n7. Delete a node\n8. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter a choice (1-6): ");
        scanf("%d", &choice);
        printf("-----------------------------------------\n");

        switch (choice) {
            case 1:
                printf("Enter a value to insert: "); scanf("%d", &val);
                root = insert(root, val);
                printf("%d inserted!\n", val);
                break;

            case 2:
                printf("BST Contents (in-order): ");
                inOrder(root);
                printf("\n");
                break;

            case 3:
                printf("BST Contents (pre-order): ");
                preOrder(root);
                printf("\n");
                break;

            case 4:
                printf("BST Contents (post-order): ");
                postOrder(root);
                printf("\n");
                break;

            case 5:
                printf("Enter value to search: ");
                scanf("%d", &val);
                int isFound = search(root, val);
                if (isFound) printf("Found!\n");
                else printf("Not found!\n");
                break;
            
            case 6:
                printf("Height of Binary Search Tree: %d levels\n", height(root));
                break;

            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &val);
                if (search(root, val)) {
                    root = deleteNode(root, val);
                    printf("%d deleted!\n", val);
                } else {
                    printf("%d was not found in the BST!\n", val);
                }
                break;

            case 8:
                printf("Freeing tree nodes and exiting program...\n");
                printf("----------------------------------------------\n");
                freeTree(root);
                root = NULL;
                break;

            default:
                printf("Enter value to search: ");
                printf("Invalid choice, please choose between 1-6!\n");
        }
    } while (choice != 6);
    return 0;
}