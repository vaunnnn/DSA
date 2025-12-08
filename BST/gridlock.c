#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PowerNode {
    int voltage;            // The Key (Unique reading)
    char *sectorName;       // Dynamic String (Requires malloc)
    struct PowerNode *left;
    struct PowerNode *right;
} PowerNode;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

// Helper to visualize the grid (In-Order Traversal)
void printGridStatus(PowerNode *root) {
    if(!root) return;

    PowerNode* stack[100];

    int top = -1;
    PowerNode* curr = root;

    while(curr != NULL || top != -1){
        while(curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];

        printf("Name: %s, Volts: %d\n",curr->sectorName, curr->voltage);
        curr = curr->right;
    }
}

// Helper to free memory (Optional for this exercise, but good to have)
void shutdownGrid(PowerNode *root) {
    if (root != NULL) {
        shutdownGrid(root->left);
        shutdownGrid(root->right);
        free(root->sectorName);
        free(root);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Add Sector (BST Insert):
// Insert a new reading into the tree based on voltage.
// CRITICAL: You must MALLOC memory for newNode->sectorName (strlen + 1) and strcpy.
// Returns the (possibly new) root of the subtree.
PowerNode* createNode(int voltage, char* name) {
    PowerNode* newNode = (PowerNode*)malloc(sizeof(PowerNode));
    newNode->sectorName = (char*)malloc(sizeof(char) * strlen(name) + 1);
    
    strcpy(newNode->sectorName, name);
    newNode->voltage = voltage;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

PowerNode* addSector(PowerNode *root, int voltage, char *name) {
    // TODO:
    // 1. Base Case: If root is NULL...
    //    a. Malloc the PowerNode struct.
    //    b. Malloc the sectorName string.
    //    c. Assign values and return new node.
    // 2. Recursion:
    //    If voltage < root->voltage, go Left.
    //    If voltage > root->voltage, go Right.
    // 3. Return root.
    if(root == NULL) {
        return createNode(voltage, name);
    }

    if(voltage < root->voltage) {
        root->left = addSector(root->left, voltage, name);
    } else if (voltage > root->voltage) {
        root->right = addSector(root->right, voltage, name);
    }
    return root;
}

// 2. Find Sector (Search):
// Look for a sector reporting a specific voltage.
// Returns the Node if found, or NULL if that voltage isn't recorded.
PowerNode* findSector(PowerNode *root, int targetVoltage) {
    // TODO: Standard BST Search logic.
    // If root is null, return null.
    // If target == root, return root.
    // If target < root, search left.
    // If target > root, search right.
    
    if(root == NULL) return NULL;

    if(root->voltage == targetVoltage) return root;

    if(targetVoltage < root->voltage) 
        return findSector(root->left, targetVoltage);
    else
        return findSector(root->right, targetVoltage);
}

// 3. Logic Check: Stability Audit (Range Count)
// Count the number of sectors where the voltage is BETWEEN minV and maxV (Inclusive).
// Optimization Hint:
// - If the current node is within range: Count it (1) + check Left + check Right.
// - If the current node is too LOW (node->voltage < minV): 
//   The valid range must be to the Right. Do not search Left.
// - If the current node is too HIGH (node->voltage > maxV):
//   The valid range must be to the Left. Do not search Right.
int countStableSectors(PowerNode *root, int minV, int maxV) {
    // TODO: Implement the recursive counting logic described above.

    if(root == NULL) return 0;

    if(root->voltage >= minV && root->voltage <= maxV) {
        return 1 + countStableSectors(root->left, minV, maxV)
                 + countStableSectors(root->right, minV, maxV);
    }

    if(root->voltage < minV) {
        return countStableSectors(root->right, minV, maxV);
    }

    return countStableSectors(root->left, minV, maxV);
}


int main() {
    PowerNode *gridRoot = NULL;

    printf("--- GRIDLOCK SYSTEM ONLINE ---\n");

    // TEST 1: Registering Live Data (Insertions)
    printf("\n[1] Receiving Telemetry...\n");
    
    // Root (Standard)
    gridRoot = addSector(gridRoot, 115, "Downtown Core"); 
    
    // Low Voltage (Brownout Risks)
    addSector(gridRoot, 100, "Old Suburbs");
    addSector(gridRoot, 90, "Abandoned Zone"); 
    addSector(gridRoot, 105, "Residential Block A");

    // High Voltage (Surge Risks)
    addSector(gridRoot, 130, "Industrial Park");
    addSector(gridRoot, 125, "Neon District");
    addSector(gridRoot, 220, "Power Plant Main");

    printf(">> Current Grid Status (Sorted by Voltage):\n");
    printGridStatus(gridRoot);

    // TEST 2: Searching Specific Readings
    printf("\n[2] Verifying Surge in Industrial Park (130V)...\n");
    PowerNode *alert = findSector(gridRoot, 130);
    if (alert) printf(">> CONFIRMED: %s is reporting %dV.\n", alert->sectorName, alert->voltage);
    else printf(">> ERROR: Signal not found.\n");

    // TEST 3: The Stability Audit (Range Logic)
    // We want to count how many sectors are "Safe".
    // Let's assume Safe Range is 105V to 125V (Inclusive).
    // Expected Matches:
    // - Residential Block A (105)
    // - Downtown Core (115)
    // - Neon District (125)
    // Expected Count: 3
    // Excluded: 90, 100 (Too Low), 130, 220 (Too High)
    
    printf("\n[3] Auditing Safe Zones (105V - 125V)...\n");
    int safeCount = countStableSectors(gridRoot, 105, 125);
    printf(">> Sectors within Safe Limits: %d (Expected: 3)\n", safeCount);

    if (safeCount == 3) printf(">> AUDIT SUCCESS: Logic Verified.\n");
    else printf(">> AUDIT FAILURE: Check your recursion.\n");

    // TEST 4: Cleanup
    printf("\n[4] Shutting down grid...\n");
    shutdownGrid(gridRoot);
    printf(">> System Offline.\n");
    
    return 0;
}
