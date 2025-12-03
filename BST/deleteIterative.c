#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_KEY_LEN 100

// 1. Structure Definition
typedef struct node {
   char *key;          // The string element used for comparison and storage
   struct node* LC;   // Left Child pointer
   struct node* RC;   // Right Child pointer
} Node, *BST;

Node* createNode(const char* key_data);
void insert(BST *tree, const char *key_data);
void inorderTraversal(BST tree);
void preorderTraversal(BST tree);
void postorderTraversal(BST tree);
void destroyTree(BST tree);

BST deleteNode(BST root, const char *key_data) {
    // TODO...
    BST* curr = &root;
    
    while(*curr != NULL && strcmp((*curr)->key, key_data) != 0) {
        curr = (strcmp((*curr)->key, key_data) > 0) ? &(*curr)->LC : &(*curr)->RC;
    }
    
    if(*curr == NULL) {
        printf("Key \"%s\" not found for deletion.\n", key_data);
        return root;
    }
    
    Node* temp = *curr;
    
    if(temp->LC == NULL && temp->RC == NULL) {
        free(temp);
        *curr = NULL;
    } else if (temp->LC == NULL || temp->RC == NULL) {
        Node* child = (temp->LC != NULL) ? temp->LC : temp->RC;
        *curr = child;
        free(temp);
    } else {
        BST* succ = &temp->RC;
        
        while((*succ)->LC != NULL) {
            succ = &(*succ)->LC;
        }
        
        strcpy(temp->key, (*succ)->key);
        
        Node* toDelete = *succ;
        *succ = (toDelete->RC != NULL) ? toDelete->RC : toDelete->LC;
        free(toDelete);
    }
    
    return root;
}

int main() {
    // 1. Create and initialize the tree
    BST myTree = NULL;

    printf("--- Building BST for Deletion Test ---\n");
    // Keys: Apple, Banana, Grape, Kiwi, Mango(ROOT), Orange, Pineapple
    insert(&myTree, "Mango");      // Root
    insert(&myTree, "Apple");      // Left of Mango
    insert(&myTree, "Pineapple");  // Right of Mango
    insert(&myTree, "Banana");     // Right of Apple
    insert(&myTree, "Grape");      // Left of Pineapple
    insert(&myTree, "Orange");     // Right of Grape
    insert(&myTree, "Kiwi");       // Left of Orange

    printf("\nInitial In-Order Traversal:\n   ");
    inorderTraversal(myTree);
    printf("\n");

    // --- Deletion Tests ---

    printf("\n--- Test 1: Delete Leaf Node (Kiwi) ---\n");
    // Kiwi is a leaf node (0 children)
    myTree = deleteNode(myTree, "Kiwi");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 2: Delete Node with 1 Child (Apple) ---\n");
    // Apple has 1 child (Banana)
    myTree = deleteNode(myTree, "Apple");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 3: Delete Node with 2 Children (Mango - the Root) ---\n");
    // Mango is replaced by its successor (Orange)
    myTree = deleteNode(myTree, "Mango");
    printf("Resulting Traversal: ");
    inorderTraversal(myTree);
    printf("\n");

    printf("\n--- Test 4: Delete Non-Existent Key (Zebra) ---\n");
    myTree = deleteNode(myTree, "Zebra");
    printf("No change expected: ");
    inorderTraversal(myTree);
    printf("\n");

    // 2. Clean up memory
    destroyTree(myTree);
    printf("\nTree destroyed and memory freed.\n");

    return 0;
}

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