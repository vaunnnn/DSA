#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_IDS 50
#define EMPTY -1

// --- Advanced Structure Definitions ---

typedef struct PatientNode {
    int patientID;          // Unique ID
    char *name;             // DYNAMIC: Must be malloc'd
    char *location;         // DYNAMIC: Must be malloc'd (e.g., "City Hospital", "Market")
    struct PatientNode *next;
} PatientNode;

typedef struct {
    int rootID;
    // Index = The Infector's ID. 
    // The List = The people they infected (Children).
    PatientNode* transmissionMap[MAX_IDS]; 
} VectorTree;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

void initVector(VectorTree *vt) {
    vt->rootID = EMPTY;
    for (int i = 0; i < MAX_IDS; i++) {
        vt->transmissionMap[i] = NULL;
    }
}

void setIndexCase(VectorTree *vt, int id) {
    vt->rootID = id;
    printf("[System] Index Case (Patient Zero) identified as ID: %d\n", id);
}

// Helper to free all memory (nodes AND strings)
void freeVector(VectorTree *vt) {
    for (int i = 0; i < MAX_IDS; i++) {
        PatientNode* curr = vt->transmissionMap[i];
        while (curr != NULL) {
            PatientNode* toDelete = curr;
            curr = curr->next;
            
            // Critical: Free the strings inside the node first
            if(toDelete->name) free(toDelete->name);
            if(toDelete->location) free(toDelete->location);
            
            free(toDelete);
        }
        vt->transmissionMap[i] = NULL;
    }
    printf("[System] Memory cleanup complete.\n");
}

// --- YOUR TASKS START HERE ---

/**
 * 1. recordInfection
 * Adds a new patient to the records as a child of the infector.
 * @param vt: Pointer to the tree
 * @param infectorID: The ID of the person passing the virus
 * @param childID: The ID of the new patient
 * @param name: The new patient's name
 * @param loc: The location where infection occurred
 * * Instructions:
 * - Malloc a new PatientNode.
 * - Malloc memory for newNode->name and copy the 'name' string into it.
 * - Malloc memory for newNode->location and copy the 'loc' string into it.
 * - Insert this node at the HEAD of the linked list at vt->transmissionMap[infectorID].
 */

PatientNode* createNode(int childID, char *name, char *loc) {
    PatientNode* newNode = (PatientNode*)malloc(sizeof(PatientNode));
    newNode->name = (char*)malloc(sizeof(char) * strlen(name));
    newNode->location = (char*)malloc(sizeof(char) * strlen(loc));

    newNode->patientID = childID;
    strcpy(newNode->name, name);
    strcpy(newNode->location, loc);
    newNode->next = NULL;
    
    return newNode;    
}
void recordInfection(VectorTree *vt, int infectorID, int childID, char *name, char *loc) {
    // TODO: Write your code here. WATCH YOUR MEMORY ALLOCATION!
    PatientNode* newPatient = createNode(childID, name, loc);
    newPatient->next = vt->transmissionMap[infectorID];
    vt->transmissionMap[infectorID] = newPatient;

    printf("Added to Record: ID: %d, Name: %s, Location: %s\n", childID, name, loc);
}

/**
 * 2. countCasesInLocation
 * Recursively counts how many direct OR indirect descendants caught the virus 
 * in a specific location type.
 * @param vt: Pointer to the tree
 * @param currentID: The ID to start searching from (e.g., Patient Zero)
 * @param targetLoc: The location string to match (e.g., "Airport")
 * @return: The total count of matching cases in this subtree.
 * * Instructions:
 * - Check the direct children of currentID.
 * - If a child's location matches 'targetLoc', count = 1, else count = 0.
 * - Add the result of a recursive call for that child's subtree.
 * - Note: The 'currentID' itself is not checked, only its children/descendants.
 */
int countCasesInLocation(VectorTree *vt, int currentID, char *targetLoc) {
    // TODO: Write recursive logic here.
    int count = 0;
    PatientNode* curr = vt->transmissionMap[currentID];
    while(curr != NULL) {
        if(strcmp(curr->location, targetLoc) == 0) {
            count++;
        }
        count += countCasesInLocation(vt, curr->patientID, targetLoc);
        curr = curr->next;
    }

    return count; 
}

/**
 * 3. tracePatientZero (The Logic Challenge)
 * Prints the transmission path from a specific patient BACK to Patient Zero.
 * Format: "Patient [ID] <- Patient [ID] <- ... <- Patient Zero"
 * @param vt: Pointer to the tree
 * @param targetID: The patient to trace back
 * * Instructions:
 * - This requires a "Reverse Lookup".
 * - Print the current targetID.
 * - If targetID == rootID, stop.
 * - Otherwise, search the ENTIRE transmissionMap array to find which index (Infector)
 * has 'targetID' in their linked list.
 * - Update targetID to that infector's ID and repeat until you hit Root.
 * - If the chain is broken (parent not found), print " <- UNKNOWN".
 */
void tracePatientZero(VectorTree *vt, int targetID) {
    // TODO: Write iterative reverse lookup logic here.

    while (1) {

        printf("Patient [%d]", targetID);

        if (targetID == vt->rootID) {
            return;
        }

        printf(" <- ");

        int foundInfector = -1;

        for (int i = 0; i < MAX_IDS; i++) {
            PatientNode* curr = vt->transmissionMap[i];

            while (curr != NULL) {
                if (curr->patientID == targetID) {
                    foundInfector = i;
                    break;
                }
                curr = curr->next;
            }

            if (foundInfector != -1) break;
        }

        if (foundInfector == -1) {
            printf("UNKNOWN");
            return;
        }

        // Move upward
        targetID = foundInfector;
    }

}


int main() {
    VectorTree outbreak;
    initVector(&outbreak);

    // --- Build the Transmission Tree ---
    // Structure:
    // P0 (Root) @ Airport
    //   -> P1 "Alice" @ "Airport"
    //   -> P2 "Bob"   @ "Cafe"
    //
    // P1 (Alice)
    //   -> P3 "Charlie" @ "Home"
    //   -> P4 "Diana"   @ "Airport"
    //
    // P2 (Bob)
    //   -> P5 "Evan"    @ "Cafe"
    
    printf("\n--- [Test 1] Recording Infections (Dynamic Memory) ---\n");
    setIndexCase(&outbreak, 0);

    // P0 infects P1 and P2
    recordInfection(&outbreak, 0, 1, "Alice", "Airport");
    recordInfection(&outbreak, 0, 2, "Bob", "Cafe");

    // P1 infects P3 and P4
    recordInfection(&outbreak, 1, 3, "Charlie", "Home");
    recordInfection(&outbreak, 1, 4, "Diana", "Airport");

    // P2 infects P5
    recordInfection(&outbreak, 2, 5, "Evan", "Cafe");

    // Verify basic structure
    PatientNode *p0_kids = outbreak.transmissionMap[0];
    if (p0_kids != NULL) {
        printf("P0 infected: %s (%s) and %s (%s)\n", 
            p0_kids->name, p0_kids->location, 
            p0_kids->next->name, p0_kids->next->location);
        // Note: Output order depends on your Head Insertion logic (LIFO)
    } else {
        printf("FAILED: P0 has no children.\n");
    }

    // --- [Test 2] Recursive Location Counting ---
    printf("\n--- [Test 2] Counting Airport Cases ---\n");
    
    // We want to know how many descendants of P0 were infected at the "Airport".
    // P1 (Airport), P4 (Airport). Total = 2.
    // P2 (Cafe), P3 (Home), P5 (Cafe).
    int airportCases = countCasesInLocation(&outbreak, 0, "Airport");
    printf("Cases at 'Airport' downstream of P0: %d (Expected: 2)\n", airportCases);
    
    int cafeCases = countCasesInLocation(&outbreak, 0, "Cafe");
    printf("Cases at 'Cafe' downstream of P0: %d (Expected: 2)\n", cafeCases); // Bob and Evan


    // --- [Test 3] Tracing Patient Zero (Reverse Logic) ---
    printf("\n--- [Test 3] Tracing Transmission Path ---\n");
    
    // Trace P5 (Evan). Expected: 5 <- 2 <- 0
    printf("Tracing P5: ");
    tracePatientZero(&outbreak, 5); 
    printf("\n");

    // Trace P4 (Diana). Expected: 4 <- 1 <- 0
    printf("Tracing P4: ");
    tracePatientZero(&outbreak, 4);
    printf("\n");

    // Trace P0. Expected: 0
    printf("Tracing P0: ");
    tracePatientZero(&outbreak, 0);
    printf("\n");

    // Clean up
    printf("\n");
    freeVector(&outbreak); // This tests if your mallocs were done correctly!

    return 0;
}


