#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 15
#define ROOT -1
#define EMPTY -2

typedef struct Node {
    int index;
    struct Node *next;
} Node;

typedef struct {
    int root;
    Node* children[MAX];
    // Helper array to quickly find if an index is already used/in the tree
    // Not strictly necessary, but helpful for error checking (we will ignore this for simplicity here)
} Tree;

// --- Helper Prototypes (matching your code) ---

void init(Tree* T);
void makeRoot(Tree* T, int index);
void addChild(Tree* T, int parent, int index);
int getParent(Tree* T, int child); // Provided
void freeTree(Tree* T); // Provided

// --- YOUR FUNCTIONS TO CODE (Prototypes) ---
int countSubordinates(Tree* T, int manager);
bool isSibling(Tree* T, int nodeA, int nodeB);
int findManagerLevel(Tree* T, int targetLevel);

// --- Provided Helper Function Implementations ---

void init(Tree* T){
    for (int i = 0; i < MAX; i++)
        T->children[i] = NULL;
    T->root = EMPTY;
}

void makeRoot(Tree* T, int index){
    T->root = index;
}

void addChild(Tree* T, int parent, int index){
    Node* child = (Node*)malloc(sizeof(Node));
    if (child == NULL) return; 
    
    child->index = index;
    // Head insertion (LIFO sibling order)
    child->next = T->children[parent];
    T->children[parent] = child;
}

// O(N*C) where N is array size, C is max children count - inefficient but works.
int getParent(Tree* T, int child){
    if (T->root == child) return ROOT;

    for (int i = 0; i < MAX; i++){
        Node* curr = T->children[i];
        while (curr != NULL){
            if (curr->index == child)
                return i;
            curr = curr->next;
        }
    }

    return EMPTY;
}

void freeTree(Tree* T){
    for (int i = 0; i < MAX; i++){
        Node* curr = T->children[i];
        while (curr != NULL){
            Node* toDelete = curr;
            curr = curr->next;
            free(toDelete);
        }
        T->children[i] = NULL;
    }
    T->root = EMPTY;
}

// --- YOUR FUNCTIONS TO IMPLEMENT ---

/**
 * 1. countSubordinates (Intermediate - Requires Recursive Traversal)
 * Counts the total number of employees that report directly or indirectly 
 * to the given manager index (i.e., the size of the subtree).
 * @param T: The tree structure
 * @param manager: The index of the manager/node to start counting from
 * @return: The total count of descendants (excluding the manager itself)
 */
int countSubordinates(Tree* T, int manager) {
    // TODO: Implement this function recursively.
    return 0; 
}

/**
 * 2. isSibling (Basic - Requires Parent Search and Sibling List Iteration)
 * Checks if two employees share the same direct manager.
 * @param T: The tree structure
 * @param nodeA: Index of the first employee
 * @param nodeB: Index of the second employee
 * @return: true if they are siblings (share the same parent), false otherwise.
 * * Note: A node is NOT a sibling of itself.
 */
bool isSibling(Tree* T, int nodeA, int nodeB) {
    // TODO: Implement this function using getParent().
    return false;
}

/**
 * 3. findManagerLevel (Logic Challenge - Requires BFS or DFS with Level Tracking)
 * Finds the index of the first manager/employee found at a specific level (depth) 
 * of the tree. The root is level 0.
 * @param T: The tree structure
 * @param targetLevel: The depth to search (e.g., 1 for direct children of root)
 * @return: The index of the first node found at targetLevel, or EMPTY if none exist.
 * * Hint: BFS is generally cleaner for level-based searches. You'll need a queue (or similar structure)
 * or a complex recursive DFS with level passing.
 */
int findManagerLevel(Tree* T, int targetLevel) {
    // TODO: Implement this function. BFS is recommended.
    return EMPTY; 
}

// Helper for BFS (required for logic function) - use a simple array-based queue for indices
int queue[MAX];
int head = 0;
int tail = 0;

void enqueue(int index) {
    if (tail < MAX) {
        queue[tail++] = index;
    }
}

int dequeue() {
    if (head < tail) {
        return queue[head++];
    }
    return EMPTY; // Queue empty
}

// Helper to reset the queue for multiple tests
void resetQueue() {
    head = 0;
    tail = 0;
}


int main() {
    Tree T;
    init(&T);

    // --- Build Tree (Same structure as your example) ---
    // Structure:
    //         0 (CEO) - Level 0
    //       /   |   \
    //      3    2    1   - Level 1 (Insertion order: 1, 2, 3)
    //     / \   | 
    //    5   4  6        - Level 2 (Insertion order: 5, 4 for 3; 6 for 2)
    // Node indices 1, 4, 5, 6 are leaves.

    makeRoot(&T, 0);
    addChild(&T, 0, 1);
    addChild(&T, 0, 2);
    addChild(&T, 0, 3);

    addChild(&T, 3, 4);
    addChild(&T, 3, 5);

    addChild(&T, 2, 6);

    printf("--- Tree Built ---\n");
    // This is the output order due to LIFO insertion: 3 -> 2 -> 1
    printf("Children of 0: ");
    Node* curr = T.children[T.root];
    while (curr != NULL) {
        printf("%d ", curr->index);
        curr = curr->next;
    }
    printf("\n\n");

    // ==========================================================
    // [TEST 1] countSubordinates (Recursive Subtree Size)
    // ==========================================================
    printf("--- TEST 1: countSubordinates ---\n");

    // Test 1a: CEO (Expected: 6 total employees)
    int count0 = countSubordinates(&T, 0); 
    printf("Subordinates under 0 (CEO): %d (Expected: 6)\n", count0);
    if (count0 == 6) printf("-> PASSED\n"); else printf("-> FAILED\n");

    // Test 1b: Manager 3 (Expected: 2: nodes 4 and 5)
    int count3 = countSubordinates(&T, 3);
    printf("Subordinates under 3: %d (Expected: 2)\n", count3);
    if (count3 == 2) printf("-> PASSED\n"); else printf("-> FAILED\n");

    // Test 1c: Leaf node 1 (Expected: 0)
    int count1 = countSubordinates(&T, 1);
    printf("Subordinates under 1: %d (Expected: 0)\n", count1);
    if (count1 == 0) printf("-> PASSED\n"); else printf("-> FAILED\n");

    printf("---------------------------------\n\n");


    // ==========================================================
    // [TEST 2] isSibling (Shared Parent Check)
    // ==========================================================
    printf("--- TEST 2: isSibling ---\n");

    // Test 2a: Siblings 4 and 5 (Expected: true)
    bool sib4_5 = isSibling(&T, 4, 5); 
    printf("4 and 5 are siblings: %s (Expected: Yes)\n", sib4_5 ? "Yes" : "No");
    if (sib4_5) printf("-> PASSED\n"); else printf("-> FAILED\n");

    // Test 2b: Non-siblings 6 and 5 (Expected: false)
    bool sib6_5 = isSibling(&T, 6, 5);
    printf("6 and 5 are siblings: %s (Expected: No)\n", sib6_5 ? "Yes" : "No");
    if (!sib6_5) printf("-> PASSED\n"); else printf("-> FAILED\n");

    // Test 2c: Self-check 3 and 3 (Expected: false)
    bool sib3_3 = isSibling(&T, 3, 3);
    printf("3 and 3 are siblings: %s (Expected: No)\n", sib3_3 ? "Yes" : "No");
    if (!sib3_3) printf("-> PASSED\n"); else printf("-> FAILED\n");

    printf("---------------------------------\n\n");


    // ==========================================================
    // [TEST 3] findManagerLevel (BFS/Level-Based Traversal)
    // ==========================================================
    printf("--- TEST 3: findManagerLevel ---\n");
    
    // The LIFO insertion order is: 3 -> 2 -> 1 (for children of 0).
    // The children are traversed in the order they appear in the list.

    // Test 3a: Level 0 (Expected: 0)
    resetQueue();
    int level0 = findManagerLevel(&T, 0); 
    printf("First manager at Level 0: %d (Expected: 0)\n", level0);
    if (level0 == 0) printf("-> PASSED\n"); else printf("-> FAILED\n");
    
    // Test 3b: Level 1 (Expected: 3, due to LIFO insertion being head first)
    resetQueue();
    int level1 = findManagerLevel(&T, 1); 
    printf("First manager at Level 1: %d (Expected: 3)\n", level1);
    if (level1 == 3) printf("-> PASSED\n"); else printf("-> FAILED\n");
    
    // Test 3c: Level 2 (Expected: 5, because 3's children 5, 4 are processed before 2's child 6)
    resetQueue();
    int level2 = findManagerLevel(&T, 2); 
    printf("First manager at Level 2: %d (Expected: 5)\n", level2);
    if (level2 == 5) printf("-> PASSED\n"); else printf("-> FAILED\n");
    
    // Test 3d: Level 3 (Expected: -2/EMPTY)
    resetQueue();
    int level3 = findManagerLevel(&T, 3); 
    printf("First manager at Level 3: %d (Expected: -2)\n", level3);
    if (level3 == EMPTY) printf("-> PASSED\n"); else printf("-> FAILED\n");

    printf("---------------------------------\n\n");


    // Clean up memory
    freeTree(&T);
    printf("Memory freed. Review complete.\n");

    return 0;
}
