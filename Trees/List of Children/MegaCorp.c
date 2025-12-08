#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_EMPLOYEES 20


// The Linked List Node (A child in the list of children)
typedef struct ChildNode {
    int childIndex;             // ID of the subordinate
    struct ChildNode *next;     // Pointer to next sibling
} ChildNode;


// The Main Array Struct
typedef struct {
    char *name;                 // Dynamic Name (malloc required)
    ChildNode *childrenHead;    // Head of the list of children IDs
} Employee;


typedef struct {
    Employee pool[MAX_EMPLOYEES]; // The Array of Linked Lists
    int rootIndex;              // ID of the CEO
    int count;                  // Total employees in system
} OrgChart;


// --- HELPER FUNCTIONS (ALREADY DONE) ---


void initOrgChart(OrgChart *org) {
    org->count = 0;
    org->rootIndex = -1;
    for(int i=0; i<MAX_EMPLOYEES; i++) {
        org->pool[i].childrenHead = NULL;
        org->pool[i].name = NULL;
    }
}


// Register a new employee in the array (Allocates name)
// Returns the new ID (index).
int hireEmployee(OrgChart *org, char *name) {
    if (org->count >= MAX_EMPLOYEES) return -1;
    int id = org->count;
    
    // Allocate name
    org->pool[id].name = (char*)malloc(strlen(name) + 1);
    strcpy(org->pool[id].name, name);
    
    org->pool[id].childrenHead = NULL; // No children yet
    org->count++;
    return id;
}


void printOrgChart(OrgChart *org) {
    printf("--- MEGACORP STRUCTURE ---\n");
    for (int i = 0; i < org->count; i++) {
        printf("[%d] %s reports: ", i, org->pool[i].name);
        ChildNode *curr = org->pool[i].childrenHead;
        if (!curr) printf("(None)");
        while (curr) {
            printf("-> [%d] ", curr->childIndex);
            curr = curr->next;
        }
        printf("\n");
    }
}


// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---


// 1. Assign Manager (Add Child):
// Make 'childID' report to 'managerID'.
// Logic: Create a new ChildNode containing childID.
// Insert it at the FRONT of managerID's linked list (pool[managerID].childrenHead).
ChildNode* createNode(int childID) {
    ChildNode* newNode = (ChildNode*)malloc(sizeof(ChildNode));

    newNode->childIndex = childID;
    newNode->next = NULL;
    
    return newNode;
}

void addReport(OrgChart *org, int managerID, int childID) {
    ChildNode* newNode = createNode(childID);
    newNode->next = org->pool[managerID].childrenHead;
    org->pool[managerID].childrenHead = newNode;
}


// 2. Count Direct Reports:
// Simply count the nodes in the linked list for a specific manager.
int countDirectReports(OrgChart *org, int managerID) {
    // TODO: Traverse the linked list at pool[managerID].childrenHead.
    // Return the count.
    ChildNode* curr = org->pool[managerID].childrenHead;
    int count = 0;

    while(curr != NULL) {
        count++;
        curr = curr->next;
    }
    return count;
}


// 3. Logic Check: Total Team Size (Recursive)
// Count ALL subordinates under a manager (Direct reports + their reports + etc.)
// This requires Depth First Search (DFS) or Recursion.
int getTotalTeamSize(OrgChart *org, int managerID) {
    // TODO:
    // 1. Initialize count = 0.
    // 2. Loop through the linked list of children for managerID.
    // 3. For each child, add 1 (the child themselves) + getTotalTeamSize(org, childIndex).
    // 4. Return total.
    ChildNode* curr = org->pool[managerID].childrenHead;
    int count = 0;
    while(curr != NULL) {
        count++;
        count += getTotalTeamSize(org, curr->childIndex);
        curr = curr->next;
    }
    return count;
}

int main() {
    OrgChart megaCorp;
    initOrgChart(&megaCorp);


    printf("--- HR SYSTEM BOOTING ---\n");


    // TEST 1: Hiring Staff
    int ceo = hireEmployee(&megaCorp, "CEO_Stark");
    megaCorp.rootIndex = ceo;


    int vp1 = hireEmployee(&megaCorp, "VP_Pepper");
    int vp2 = hireEmployee(&megaCorp, "VP_Happy");
    
    int mgr1 = hireEmployee(&megaCorp, "Mgr_Rhodey");
    int dev1 = hireEmployee(&megaCorp, "Dev_Peter");
    int dev2 = hireEmployee(&megaCorp, "Dev_Vision");


    // TEST 2: Building Hierarchy (List of Children)
    printf("\n[1] Assigning Reporting Lines...\n");
    
    // CEO manages VPs
    addReport(&megaCorp, ceo, vp1);
    addReport(&megaCorp, ceo, vp2);


    // VP_Pepper manages Mgr_Rhodey
    addReport(&megaCorp, vp1, mgr1);


    // Mgr_Rhodey manages Devs
    addReport(&megaCorp, mgr1, dev1);
    addReport(&megaCorp, mgr1, dev2);


    printOrgChart(&megaCorp);


    // TEST 3: Simple Count
    printf("\n[2] Checking Direct Reports for CEO...\n");
    int direct = countDirectReports(&megaCorp, ceo);
    printf(">> CEO has %d direct reports (Expected: 2)\n", direct);


    // TEST 4: Recursive Logic (Total Team Size)
    // Structure:
    // CEO -> VP_Pepper -> Mgr_Rhodey -> [Dev_Peter, Dev_Vision] (4 people under CEO on this branch)
    // CEO -> VP_Happy (1 person under CEO on this branch)
    // Total subordinates under CEO = 5.
    
    printf("\n[3] Calculating Total Team Size for CEO (Recursive)...\n");
    int total = getTotalTeamSize(&megaCorp, ceo);
    printf(">> Total subordinates under CEO: %d (Expected: 5)\n", total);
    
    if (total == 5) printf(">> LOGIC SUCCESS.\n");
    else printf(">> LOGIC FAILURE.\n");


    // Check sub-team
    int subTeam = getTotalTeamSize(&megaCorp, mgr1);
    printf(">> Total subordinates under Mgr_Rhodey: %d (Expected: 2)\n", subTeam);


    // Cleanup Memory (Optional for exam practice)
    printf("\n[4] Cleaning up memory...\n");
    for(int i=0; i<megaCorp.count; i++) {
        free(megaCorp.pool[i].name);
        
        // Also free the linked list of children!
        ChildNode *curr = megaCorp.pool[i].childrenHead;
        while(curr != NULL) {
            ChildNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    printf(">> Memory Freed.\n");


    return 0;
}
