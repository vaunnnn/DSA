#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_AGENTS 20 // The maximum ID an agent can have

// A node in the linked list representing a subordinate Agent (Asset)
typedef struct Node {
    int agentID;        // The ID of the child agent
    struct Node* next;  // Pointer to the next sibling
} Node;

// The Network Wrapper
typedef struct {
    // Array of pointers. 
    // index = Handler's ID. 
    // list = Linked list of Assets (children) managed by this Handler.
    Node* handlerList[MAX_AGENTS]; 
} SpyNetwork;


// --- HELPER FUNCTIONS (PRE-MADE) ---

// Initialize all headers to NULL
void initNetwork(SpyNetwork* net) {
    for (int i = 0; i < MAX_AGENTS; i++) {
        net->handlerList[i] = NULL;
    }
}

// Helper to create a node
Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->agentID = id;
    newNode->next = NULL;
    return newNode;
}

// Visualizes the immediate children of all active handlers
void printNetwork(SpyNetwork* net) {
    printf("Current Network Topology:\n");
    for (int i = 0; i < MAX_AGENTS; i++) {
        if (net->handlerList[i] != NULL) {
            printf("  Handler [%d] manages: ", i);
            Node* temp = net->handlerList[i];
            while (temp != NULL) {
                printf("-> [Agent %d] ", temp->agentID);
                temp = temp->next;
            }
            printf("\n");
        }
    }
}

// --- YOUR TASKS START HERE ---

/* * TASK 1: Recruit Asset (Insert)
 * Add 'assetID' to the end of the linked list of 'handlerID'.
 * * Params:
 * net: pointer to SpyNetwork
 * handlerID: the index of the parent
 * assetID: the value to insert into the list
 */
void recruitAsset(SpyNetwork* net, int handlerID, int assetID) {
    // 1. Create the new node using createNode()
    // 2. Check if the handlerList[handlerID] is NULL (empty list). 
    //    If yes, make the new node the head.
    // 3. If not, traverse to the end of the linked list and link the new node.
    
    // TODO: Write your code here
    Node* curr = net->handlerList[handlerID];
    Node* newNode = createNode(assetID);
    if(curr == NULL) {
        net->handlerList[handlerID] = newNode;
        return;
    }

    while(curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = newNode;
}

/* * TASK 2: Disavow Agent (Delete)
 * Find 'targetID' in the list of 'handlerID' and remove it.
 * Free the memory of the removed node.
 * * Params:
 * net: pointer to SpyNetwork
 * handlerID: the index of the parent
 * targetID: the specific child to remove
 */
void disavowAgent(SpyNetwork* net, int handlerID, int targetID) {
    // 1. Handle empty list case.
    // 2. Handle case where target is the head (first node).
    // 3. Handle case where target is in the middle or end (traversal).
    
    // TODO: Write your code here
    Node* curr = net->handlerList[handlerID];
    Node* prev = NULL;
    if(curr == NULL) {
        return;
    }

    while(curr != NULL && curr->agentID != targetID) {
        prev = curr;
        curr = curr->next;
    }

    if(prev == NULL) {
        net->handlerList[handlerID] = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
}

/* * TASK 3: Get Downline Size (Logic & Traversal)
 * Recursively count the TOTAL number of subordinates under an agent.
 * This includes direct children, grandchildren, great-grandchildren, etc.
 * * Logic Hint: 
 * - Iterate through the immediate children of the given agentID.
 * - For every child found, add 1 (the child itself) + the result of a recursive call on that child.
 */
int getDownlineSize(SpyNetwork* net, int agentID) {
    // 1. Get the head of the linked list for this agent (net->handlerList[agentID])
    // 2. Iterate through the list.
    // 3. For every node, count++ AND add getDownlineSize(net, node->agentID)
    
    // TODO: Write your code here
    int count = 0;
    
    Node* curr = net->handlerList[agentID];

    while(curr != NULL) {
        count++;
        count += getDownlineSize(net, curr->agentID);
        curr = curr->next;
    }
    
    return count;
}


int main() {
    SpyNetwork argus;
    initNetwork(&argus);

    printf("=== OPERATION SHADOW TREE ===\n\n");

    // 1. RECRUITMENT PHASE
    printf("--- Phase 1: Recruitment ---\n");
    // Agent 0 is the Director
    recruitAsset(&argus, 0, 1); // 0 recruits 1
    recruitAsset(&argus, 0, 2); // 0 recruits 2
    recruitAsset(&argus, 0, 3); // 0 recruits 3
    
    // Agent 1 builds their team
    recruitAsset(&argus, 1, 4);
    recruitAsset(&argus, 1, 5);

    // Agent 2 builds their team
    recruitAsset(&argus, 2, 6);

    // Agent 5 (sub of 1) recruits someone
    recruitAsset(&argus, 5, 7);

    printNetwork(&argus);

    // 2. LOGIC PHASE: CALCULATE DOWNLINE
    printf("\n--- Phase 2: Intelligence Reach ---\n");
    // We want to know how many total agents are under Agent 1 (Direct + Indirect)
    // Agent 1 has direct: 4, 5. Indirect: 7 (under 5). Total should be 3.
    int reach1 = getDownlineSize(&argus, 1);
    printf("Agent 1 Total Downline Size: %d (Expected: 3)\n", reach1);

    int reach0 = getDownlineSize(&argus, 0);
    printf("Director (0) Total Network Size: %d (Expected: 7)\n", reach0);
    
    // 3. BURN NOTICE (DELETION)
    printf("\n--- Phase 3: Burn Notice (Deletion) ---\n");
    printf("Disavowing Agent 2 (Removes Agent 2 from Director's list)...\n");
    
    disavowAgent(&argus, 0, 2); // Remove child 2 from parent 0
    
    printNetwork(&argus);

    // Verify logic after deletion
    // Agent 2 had 6 under him. Since 2 is cut from 0, 0 can no longer reach 6.
    // Note: In this specific array implementation, 2's list still exists at index 2, 
    // but 2 is no longer a child of 0.
    int newReach0 = getDownlineSize(&argus, 0); 
    printf("Director (0) New Network Size: %d (Expected: 5)\n", newReach0);
    // (Remaining: 1, 3, 4, 5, 7)

    return 0;
}
