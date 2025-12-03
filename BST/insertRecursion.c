#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a maximum length for the key
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;

Node* createNode(const char* key_data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = (char*)malloc(sizeof(char) * MAX_KEY_LEN);
    strcpy(newNode->key, key_data);
    newNode->LC = NULL;
    newNode->RC = NULL;
    return newNode;
}

void insert(BST *tree, const char *key_data) {
    // TODO...
    if(*tree == NULL) {
        Node* newNode = createNode(key_data);
        *tree = newNode;
        printf("Inserted key: \"%s\"\n", (*tree)->key);
        return;
    } 
    
    if (strcmp((*tree)->key, key_data) > 0) {
        insert(&(*tree)->LC, key_data);
    } else if (strcmp((*tree)->key, key_data) < 0) {
        insert(&(*tree)->RC, key_data);
    } else {
        printf("Key \"%s\" already exists. Ignoring.\n", key_data);
    }
}

void inorderTraversal(BST tree) {
    // TODO...
    if(tree == NULL) return;
    
    inorderTraversal(tree->LC);
    printf("\"%s\" ", tree->key);
    inorderTraversal(tree->RC);
}

void preorderTraversal(BST tree) {
    // TODO...
    if(tree == NULL) return;
    
    printf("\"%s\" ", tree->key);
    preorderTraversal(tree->LC);
    preorderTraversal(tree->RC);
}

void postorderTraversal(BST tree) {
    // TODO...
    if(tree == NULL) return;
    
    postorderTraversal(tree->LC);
    postorderTraversal(tree->RC);
    printf("\"%s\" ", tree->key);
}

/**
 * @brief Frees all memory allocated for the BST nodes, including the string keys.
 * * @param tree The root of the tree to destroy.
 */
void destroyTree(BST tree) {
    if (tree != NULL) {
        destroyTree(tree->LC);
        destroyTree(tree->RC);

        if (tree->key != NULL) {
            free(tree->key);
        }

        free(tree);
    }
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Initializing and Inserting String Data into BST ---\n");

    // Root: 'Mango'
    // Left: 'Apple', 'Banana'
    // Right: 'Pineapple', 'Grape', 'Orange', 'Kiwi'
    insert(&myTree, "Mango");
    insert(&myTree, "Apple");
    insert(&myTree, "Pineapple");
    insert(&myTree, "Banana");
    insert(&myTree, "Grape");
    insert(&myTree, "Orange");
    insert(&myTree, "Kiwi");

    // Test duplicate handling
    insert(&myTree, "Mango");

    printf("\n\n--- BST Traversal Results ---\n");

    // In-Order: Sorted (A, B, G, K, M, O, P)
    printf("1. In-Order Traversal (Left-Root-Right, Sorted):\n");
    printf("   ");
    inorderTraversal(myTree);
    printf("\n\n");

    // Pre-Order: Root first (M, A, B, P, G, K, O)
    printf("2. Pre-Order Traversal (Root-Left-Right):\n");
    printf("   ");
    preorderTraversal(myTree);
    printf("\n\n");

    // Post-Order: Root last (B, A, K, O, G, P, M)
    printf("3. Post-Order Traversal (Left-Right-Root):\n");
    printf("   ");
    postorderTraversal(myTree);
    printf("\n\n");

    // 3. Clean up memory
    destroyTree(myTree);
    printf("Tree destroyed and memory freed.\n");

    return 0;
}