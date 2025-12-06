#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef enum { EMPTY, OCCUPIED, DELETED } State;

typedef struct {
    char codeName[20];
    int clearanceLevel;
    State state;
} HashEntry;

typedef HashEntry HashTable[TABLE_SIZE];

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initTable(HashTable table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].state = EMPTY;
    }
}

int hashFunction(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

void printTable(HashTable table) {
    printf("--- Table Dump ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].state == OCCUPIED) 
            printf("[%d]: %s (Lvl %d)\n", i, table[i].codeName, table[i].clearanceLevel);
        else if (table[i].state == DELETED)
            printf("[%d]: X_DELETED_X\n", i);
        else 
            printf("[%d]: ...\n", i);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Insert Agent: Handle collisions using Linear Probing.
// Note: You can overwrite an entry if it is EMPTY or DELETED.
bool addAgent(HashTable table, char *name, int level) {
    // TODO: Hash the name. Loop using Linear Probing. 
    // Insert at first available spot. Return true if success, false if table full.

    int loc = hashFunction(name);
    printf("LOCATION: %d\n", loc);

    if(table[loc].state, EMPTY  || table[loc].state, DELETED ) {
        strcpy(table[loc].codeName, name);
        table[loc].clearanceLevel = level;
        table[loc].state = OCCUPIED;
        return true;
    }

    if(table[loc].state == OCCUPIED) {
        return addAgent(table, table[(loc + 1) % TABLE_SIZE].codeName, level);
    }

    return false;
}

// 2. Search Agent: Returns the index of the agent, or -1 if not found.
// Note: Remember, hitting a 'DELETED' spot does NOT mean you stop searching!
// You only stop if you find the name OR you hit 'EMPTY'.
int findAgent(HashTable table, char *name) {
    // TODO: Hash and Probe. Return index or -1.
    int loc = hashFunction(name);
    //loc = 6
    for(int i = 0; i < TABLE_SIZE; i++) {
        int idx = (loc + i) % TABLE_SIZE; // (6 + 0) % TABLE_SIZE
        if(table[idx].state == EMPTY) return -1;

        if(table[idx].state == OCCUPIED && strcmp(table[idx].codeName, name) == 0) return idx;

    }
    return -1;
}

// 3. Delete Agent: Find the agent and perform "Lazy Deletion".
// Logic: Change state to DELETED. Do not wipe the data or set to EMPTY.
bool retireAgent(HashTable table, char *name) {
    // TODO: Use find logic to locate. If found, mark DELETED. 
    // Return true if retired successfully, false if not found.
    int loc = hashFunction(name);
    if(strcmp(table[loc].codeName, name) == 0) {
        table[loc].state = DELETED;
        return true;
    } else {
        return retireAgent(table, table[(loc + 1) % TABLE_SIZE].codeName);
    }

    return false;
}

int main() {
    HashTable spyDB;
    initTable(spyDB);

    printf("--- SHADOW DATABASE INITIALIZED ---\n");

    // TEST 1: Insertions with Intentional Collisions
    // Assume TABLE_SIZE is 10.
    // 'Bond' and 'Hunt' might naturally collide or be close depending on ASCII sum.
    
    printf("\n[1] Adding Agents...\n");
    addAgent(spyDB, "Bond", 7);
    addAgent(spyDB, "Hunt", 6);
    addAgent(spyDB, "Bourne", 9); // Should probe if collision occurs
    addAgent(spyDB, "Powers", 4);
    
    printTable(spyDB);

    // TEST 2: Searching
    printf("\n[2] Searching for 'Hunt'...\n");
    int idx = findAgent(spyDB, "Hunt");
    if(idx != -1) printf("Found 'Hunt' at index %d.\n", idx);
    else printf("'Hunt' not found.\n", idx);

    // TEST 3: Lazy Deletion
    printf("\n[3] Retiring 'Bond' (Lazy Deletion)...\n");
    if(retireAgent(spyDB, "Bond")) printf("'Bond' has been retired.\n");
    
    printTable(spyDB); 
    // 'Bond' slot should show X_DELETED_X

    // TEST 4: Search Logic after Deletion
    // This is the critical test. If we search for an agent that was inserted
    // AFTER Bond (and collided), the search must skip over Bond's DELETED spot.
    printf("\n[4] Searching for 'Bourne' (Must skip over Deleted Bond)...\n");
    idx = findAgent(spyDB, "Bourne");
    if(idx != -1) printf("SUCCESS: Found 'Bourne' at index %d (Skipped deletion correctly).\n", idx);
    else printf("FAILURE: Could not find 'Bourne' (Search stopped at Deleted spot).\n");

    return 0;
}
