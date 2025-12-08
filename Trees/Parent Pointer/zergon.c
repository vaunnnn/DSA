#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HIVE_SIZE 20

typedef enum { QUEEN, WARRIOR, DRONE } Caste;

typedef struct {
    char *name;         // DYNAMIC string (malloc required)
    int psiLevel;       // Mental strength
    Caste caste;        // Type of alien
    int masterIndex;    // PARENT POINTER: Index of the superior (-1 if Root)
} AlienNode;

typedef struct {
    AlienNode pool[MAX_HIVE_SIZE];
    int count;
} HiveMind;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initHive(HiveMind *hive) {
    hive->count = 0;
}

const char* getCasteName(Caste c) {
    switch(c) {
        case QUEEN: return "QUEEN";
        case WARRIOR: return "WARRIOR";
        case DRONE: return "DRONE";
        default: return "UNKNOWN";
    }
}

void printHiveSummary(HiveMind *hive) {
    printf("--- HIVE STATUS ---\n");
    for (int i = 0; i < hive->count; i++) {
        AlienNode *a = &hive->pool[i];
        printf("[%d] %s (%s) | Master Index: %d\n", 
               i, a->name, getCasteName(a->caste), a->masterIndex);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Spawn Alien: Add a new node to the array.
// Returns the index of the new alien, or -1 if hive is full.
int spawnAlien(HiveMind *hive, char *name, int psi, Caste caste, int masterIdx) {
    if (hive->count >= MAX_HIVE_SIZE) return -1;
    
    // TODO:
    // 1. Get pointer to the next available slot (hive->pool[hive->count]).
    // 2. MALLOC memory for 'name' and copy the string.
    // 3. Set psi, caste, and masterIndex.
    // 4. Increment count and return the index where it was stored.
    hive->pool[hive->count].name = (char*)malloc(sizeof(char) * strlen(name) + 1);

    strcpy(hive->pool[hive->count].name, name);
    hive->pool[hive->count].caste = caste;
    hive->pool[hive->count].psiLevel = psi;
    hive->pool[hive->count].masterIndex = masterIdx;
    
    return hive->count++;
}

// 2. Find Queen (Find Root):
// Trace the 'masterIndex' upwards until you find the node with masterIndex == -1.
// Returns the INDEX of the Queen.
int findQueen(HiveMind *hive, int startIndex) {
    // TODO:
    // Write a loop: while current node's master != -1, move to master.
    // Return the final index found.
    int index = 0;
    if(hive->pool[startIndex].masterIndex != -1) {
        index = findQueen(hive, hive->pool[startIndex].masterIndex);
    }
    return index;
}

// 3. Logic Check: Calculate Synaptic Delay (Depth/Height)
// Count how many "hops" it takes to get from 'targetIndex' to the Queen.
// If targetIndex IS the Queen, delay is 0.
// If targetIndex is a direct child of Queen, delay is 1.
int calculateSynapticDelay(HiveMind *hive, int targetIndex) {
    // TODO: 
    // Traverse up the parent pointers (masterIndex).
    // Count the steps until you reach -1.
    // Return the count.
    int count = 0;

    if(hive->pool[targetIndex].masterIndex != -1) {
        count++;
        count += calculateSynapticDelay(hive, hive->pool[targetIndex].masterIndex);
    }

    return count;
}


int main() {
    HiveMind zergonHive;
    initHive(&zergonHive);

    printf("--- HIVE MIND AWAKENING ---\n");

    // TEST 1: Spawning the Queen (Root)
    // Master is -1 because she answers to no one.
    int queenIdx = spawnAlien(&zergonHive, "Overmind", 9000, QUEEN, -1);
    printf("Queen spawned at index: %d\n", queenIdx);

    // TEST 2: Spawning Subordinates
    // Warriors serve the Queen (Index 0).
    int w1 = spawnAlien(&zergonHive, "Hunter", 500, WARRIOR, queenIdx);
    int w2 = spawnAlien(&zergonHive, "Crusher", 600, WARRIOR, queenIdx);
    
    // Drones serve the Warriors.
    // 'WorkerA' serves 'Hunter' (Index 1)
    int d1 = spawnAlien(&zergonHive, "WorkerA", 50, DRONE, w1);
    // 'WorkerB' serves 'Crusher' (Index 2)
    int d2 = spawnAlien(&zergonHive, "WorkerB", 50, DRONE, w2);
    // 'Larva' serves 'WorkerA' (Index 3) - A deep hierarchy!
    int l1 = spawnAlien(&zergonHive, "Larva", 10, DRONE, d1);

    printHiveSummary(&zergonHive);

    // TEST 3: Finding the Root
    printf("\n[3] Tracing Lineage for 'Larva' (Index %d)...\n", l1);
    int root = findQueen(&zergonHive, l1);
    if (root == queenIdx) printf(">> SUCCESS: Trace leads to Queen 'Overmind'.\n");
    else printf(">> FAILURE: Trace ended at index %d.\n", root);

    // TEST 4: Calculating Depth (Logic)
    // Larva (5) -> WorkerA (3) -> Hunter (1) -> Queen (0).
    // This is 3 hops.
    printf("\n[4] Calculating Synaptic Delay for 'Larva'...\n");
    int delay = calculateSynapticDelay(&zergonHive, l1);
    printf(">> Delay: %d hops (Expected: 3)\n", delay);
    
    if (delay == 3) printf(">> LOGIC VERIFIED.\n");
    else printf(">> LOGIC ERROR.\n");

    // TEST 5: Cleanup (Memory)
    // In a real exam, demonstrate you know how to free the dynamic names.
    printf("\n[5] Hive Destroyed (Memory Cleanup)...\n");
    for(int i=0; i<zergonHive.count; i++) {
        free(zergonHive.pool[i].name);
    }
    printf(">> Memory Freed.\n");

    return 0;
}
