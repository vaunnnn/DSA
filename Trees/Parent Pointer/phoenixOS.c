#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MODULES 50
#define MAX_CHILDREN 10
#define NO_PARENT -1
#define ROOT_ID 0

// --- Structure Definitions ---

typedef struct {
    char name[30];
    int parentID;             // Index of its parent module
    int childIDs[MAX_CHILDREN]; // Array of indices of its children
    int numChildren;          // Current count of children
} Module;

typedef struct {
    Module modules[MAX_MODULES];
    int count; // Current number of modules in the system
} DependencyTree;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

// Initializes the tree with the core OS module
void initTree(DependencyTree *tree, char *rootName) {
    strcpy(tree->modules[0].name, rootName);
    tree->modules[0].parentID = NO_PARENT;
    tree->modules[0].numChildren = 0;
    tree->count = 1;
    printf("[System] Initialized Root Module: %s\n", rootName);
}

// Returns the index of a module by name, or -1 if not found
int getModuleID(DependencyTree *tree, char *name) {
    for (int i = 0; i < tree->count; i++) {
        if (strcmp(tree->modules[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Helper to display the entire structure
void printTreeStatus(DependencyTree *tree) {
    printf("\n--- PHOENIX OS MODULE REGISTRY ---\n");
    printf("ID | Module Name    | Parent ID | Children (IDs)\n");
    printf("---|----------------|-----------|-------------------\n");
    for(int i=0; i < tree->count; i++) {
        printf("%02d | %-14s | %-9d |", i, tree->modules[i].name, tree->modules[i].parentID);
        for(int j=0; j < tree->modules[i].numChildren; j++) {
            printf(" %d", tree->modules[i].childIDs[j]);
        }
        printf("\n");
    }
    printf("------------------------------------\n");
}

// --- YOUR TASKS START HERE ---

/**
 * 1. addNewModule
 * Creates a new module and establishes the dependency link.
 * @param tree: Pointer to the dependency tree
 * @param childName: The name of the new sub-module
 * @param parentName: The name of the existing module it depends on (parent)
 * * Instructions:
 * - Check if the tree is full or if the parent module exists.
 * - Find the parent's ID.
 * - Add the new module (child) to the end of the modules array.
 * - Set the child's parentID.
 * - CRITICAL: Add the child's new ID to the parent module's childIDs array.
 */
void addNewModule(DependencyTree *tree, char *childName, char *parentName) {
    // TODO: Write your code here
}


/**
 * 2. printDirectSubmodules
 * Prints the names of all modules that immediately depend on the given module.
 * @param tree: Pointer to the dependency tree
 * @param moduleID: The ID of the module (parent) to check
 * * Instructions:
 * - Check if the moduleID is valid.
 * - Loop through the module's childIDs array (up to numChildren).
 * - Print the name of each child module.
 */
void printDirectSubmodules(DependencyTree *tree, int moduleID) {
    // TODO: Write your code here
}


/**
 * 3. listAllDownstreamDependencies (The Logic Challenge)
 * Finds and prints the names of ALL modules (children, grandchildren, etc.)
 * that are dependent on the given module. This requires recursion (DFS/BFS).
 * @param tree: Pointer to the dependency tree
 * @param moduleID: The ID of the module (parent) to check
 * @param level: Used internally for formatting (0 for the initial call)
 * * Instructions:
 * - This function MUST be recursive.
 * - Base case: If the module has no children, return.
 * - Recursive step: Loop through the childIDs. Print the child's name (with indentation based on 'level').
 * - Call the function recursively on the child's ID, increasing the level.
 */
void listAllDownstreamDependencies(DependencyTree *tree, int moduleID, int level) {
    // TODO: Write your code here
}

// Simple helper function for indentation display
void printIndent(int level) {
    for (int i = 0; i < level; i++) {
        printf("  |-- ");
    }
}

// Wrapper to make the initial call clean for the user
void testDownstream(DependencyTree *tree, char *moduleName) {
    int id = getModuleID(tree, moduleName);
    printf("\n--- Downstream Dependencies for '%s' ---\n", moduleName);
    if (id != -1) {
        // The core recursive function call
        listAllDownstreamDependencies(tree, id, 0); 
    } else {
        printf("Module not found.\n");
    }
    printf("----------------------------------------\n");
}


int main() {
    DependencyTree phoenixTree;
    
    // 1. Initialize Root
    initTree(&phoenixTree, "OS_Core"); // Root ID 0

    // 2. Build the Tree
    // Structure:
    // OS_Core -> Kernel, Drivers
    // Kernel -> Scheduler, MemoryMgr
    // Drivers -> NetCard, Audio
    // Scheduler -> ProcessQueue
    
    printf("\n[Test 1] Adding Dependencies...\n");
    addNewModule(&phoenixTree, "Kernel", "OS_Core");
    addNewModule(&phoenixTree, "Drivers", "OS_Core");
    addNewModule(&phoenixTree, "Scheduler", "Kernel");
    addNewModule(&phoenixTree, "MemoryMgr", "Kernel");
    addNewModule(&phoenixTree, "NetCard", "Drivers");
    addNewModule(&phoenixTree, "Audio", "Drivers");
    addNewModule(&phoenixTree, "ProcessQueue", "Scheduler");

    printTreeStatus(&phoenixTree);

    // 3. Test Direct Submodules
    printf("\n[Test 2] Checking Direct Submodules (Children)...\n");
    int idKernel = getModuleID(&phoenixTree, "Kernel");
    int idDrivers = getModuleID(&phoenixTree, "Drivers");

    printf("Kernel's direct dependencies: ");
    printDirectSubmodules(&phoenixTree, idKernel); // Expected: Scheduler, MemoryMgr

    printf("Drivers' direct dependencies: ");
    printDirectSubmodules(&phoenixTree, idDrivers); // Expected: NetCard, Audio


    // 4. Test Recursive Logic (DFS/BFS traversal)
    printf("\n[Test 3] Finding ALL Downstream Dependencies...\n");
    
    // Test 4a: Full Subtree (Expected: Scheduler, MemoryMgr, ProcessQueue)
    testDownstream(&phoenixTree, "Kernel"); 

    // Test 4b: A Single leaf (Expected: Nothing)
    testDownstream(&phoenixTree, "NetCard");
    
    // Test 4c: The entire system (Expected: Everything but OS_Core)
    testDownstream(&phoenixTree, "OS_Core"); 

    return 0;
}
