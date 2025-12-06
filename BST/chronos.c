#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Structure Definitions ---
typedef struct EventNode {
    int year;            // The BST Key
    char description[50];
    struct EventNode *left;
    struct EventNode *right;
} EventNode;

typedef struct {
    EventNode *root;
} TimeCapsule;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

void initCapsule(TimeCapsule *tc) {
    tc->root = NULL;
}

EventNode* createEvent(int year, char *desc) {
    EventNode *newNode = (EventNode*)malloc(sizeof(EventNode));
    newNode->year = year;
    strcpy(newNode->description, desc);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Helper: Finds the minimum value node in a subtree (Critical for deletion)
EventNode* findMinNode(EventNode* node) {
    EventNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Helper: Displays the timeline in order
void printTimeline(EventNode *root) {
    if (root != NULL) {
        printTimeline(root->left);
        printf("[%d] %s\n", root->year, root->description);
        printTimeline(root->right);
    }
}

// --- YOUR TASKS START HERE ---

/**
 * 1. archiveEvent
 * Inserts a new event into the timeline based on year.
 * @param root: Current root of subtree
 * @param year: The year of the event
 * @param desc: Description text
 * @return: The updated root pointer
 */
EventNode* archiveEvent(EventNode *root, int year, char *desc) {
    // TODO: Implement recursive BST insertion

    if(root == NULL) {
        return createEvent(year, desc);
    }
    if(root->year > year) {
        root->left = archiveEvent(root->left, year, desc);
    } else if (root->year < year) {
        root->right = archiveEvent(root->right, year, desc);
    }
    return root; 
}

/**
 * 2. countEventsInEra (Logic Challenge)
 * Counts how many events occurred strictly between startYear and endYear (inclusive).
 * @param root: Current root of subtree
 * @param startYear: Lower bound
 * @param endYear: Upper bound
 * @return: Number of events in this range
 * * Logic Hint: If current node is smaller than startYear, don't waste time checking left.
 * If current node is larger than endYear, don't check right.
 */
int countEventsInEra(EventNode *root, int startYear, int endYear) {
    // TODO: Implement optimized recursive counting
    if(root == NULL) return 0;

    int count = 0;

    if(root->year >= startYear && root->year <= endYear) count++;

    if(root->year > startYear)
        count += countEventsInEra(root->left, startYear, endYear);

    if(root->year < endYear)
        count+= countEventsInEra(root->right, startYear, endYear);

    return count; 
}

/**
 * 3. eraseEvent
 * Deletes an event by year. This is the complex BST Deletion.
 * @param root: Current root of subtree
 * @param year: The year to delete
 * @return: The updated root pointer
 * * Instructions:
 * - Case 1: Node to be deleted is leaf (0 children).
 * - Case 2: Node has 1 child (replace with child).
 * - Case 3: Node has 2 children (find inorder successor, copy data, delete successor).
 * - Use the findMinNode() helper provided above for Case 3.
 */
EventNode* eraseEvent(EventNode *root, int year) {
    // TODO: Implement BST Deletion
    if(root == NULL) return NULL;

    if(root->year > year) {
        root->left = eraseEvent(root->left, year);
    } else if (root->year < year) {
        root->right = eraseEvent(root->right, year);
    } else {
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            EventNode* child = (root->left != NULL) ? root->left : root->right;
            root = child;
            free(root);
        } else {
            EventNode* succ = root->right;

            while(succ->left != NULL) succ = succ->left;

            strcpy(root->description, succ->description);
            root->year = succ->year;

            root->right = eraseEvent(root->right, year);
        }
    }

    return root; 
}

int main() {
    TimeCapsule chronos;
    initCapsule(&chronos);

    printf("--- [Test 1] Building Timeline (Insertion) ---\n");
    // Building a balanced-ish tree
    // Structure:
    //      1950
    //     /    \
    //   1900   2000
    //   /  \   /  \
    // 1800 1920 1980 2020
    
    chronos.root = archiveEvent(chronos.root, 1950, "Start of AI Research");
    chronos.root = archiveEvent(chronos.root, 1900, "Zeppelin Flight");
    chronos.root = archiveEvent(chronos.root, 2000, "Y2K Bug Scare");
    chronos.root = archiveEvent(chronos.root, 1800, "Voltaic Pile");
    chronos.root = archiveEvent(chronos.root, 1920, "Roaring Twenties");
    chronos.root = archiveEvent(chronos.root, 1980, "Pac-Man Released");
    chronos.root = archiveEvent(chronos.root, 2020, "Global Lockdown");

    printTimeline(chronos.root);

    printf("\n--- [Test 2] Range Query (Logic) ---\n");
    // Range 1900 to 1990 should include: 1900, 1920, 1950, 1980 (4 events)
    int count = countEventsInEra(chronos.root, 1900, 1990);
    printf("Events between 1900-1990: %d (Expected: 4)\n", count);

    printf("\n--- [Test 3] Deletion (The Hard Part) ---\n");
    
    printf("A. Deleting Leaf (1800)...\n");
    chronos.root = eraseEvent(chronos.root, 1800);
    
    printf("B. Deleting Node with 1 Child (2020 is leaf, but let's delete 2000 which has children)...\n");
    chronos.root = eraseEvent(chronos.root, 2000); // 2000 has 1980 and 2020. Complexity check.
    
    printf("C. Deleting Root with 2 Children (1950)...\n");
    chronos.root = eraseEvent(chronos.root, 1950);

    printf("\nFinal Timeline Check:\n");
    printTimeline(chronos.root);
    // 1800 gone. 2000 gone. 1950 gone.
    // Remaining should be consistent and sorted.

    return 0;
}
