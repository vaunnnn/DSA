#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5

typedef struct LootNode {
    char name[20];          // Fixed size key
    char *magicEffect;      // DYNAMIC variable (Requires malloc)
    struct LootNode *next;  // Pointer for chaining
} LootNode;

typedef LootNode* LootTable[TABLE_SIZE]; // Array of Pointers

// --- HELPER FUNCTIONS ---

int hash(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) sum += key[i];
    return sum % TABLE_SIZE;
}

void initTable(LootTable table) {
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;
}

void printTable(LootTable table) {
    printf("--- CHEST CONTENTS ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        LootNode *curr = table[i];
        while (curr != NULL) {
            printf("[%s: %s] -> ", curr->name, curr->magicEffect);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Add Loot: Insert at the FRONT of the linked list (O(1)).
// NOTE: You must MALLOC memory for 'newNode' AND 'newNode->magicEffect'.

LootNode* createNode(char* name, char* effect) {
    LootNode* newNode = (LootNode*)malloc(sizeof(LootNode));
    newNode->magicEffect = (char*)malloc(sizeof(char) * strlen(effect) + 1);

    strcpy(newNode->name, name);
    strcpy(newNode->magicEffect, effect);
    newNode->next = NULL;

    return newNode;
}

void addLoot(LootTable table, char *name, char *effect) {
    // TODO:
    // 1. Calculate hash index.
    int loc = hash(name);
    // 2. Malloc a new LootNode.
    // 3. Malloc memory for magicEffect (strlen(effect) + 1) and strcpy.
    LootNode* newNode = createNode(name, effect);
    // 4. Handle linked list insertion (Point new->next to head, update head).
    newNode->next = table[loc];
    table[loc] = newNode;
}

// 2. Find Loot: Search the chain for a specific name.
// Returns the effect string if found, or "Not Found" if missing.
char* checkLoot(LootTable table, char *name) {
    // TODO: Traverse the list at the hashed index. Return magicEffect if match found.

    int loc = hash(name);

    LootNode* curr = table[loc];

    while(curr != NULL && strcmp(curr->name, name) != 0) {
        curr = curr->next;
    }

    if(strcmp(curr->name, name) == 0) return curr->magicEffect; 

    return "Not Found";
}

// 3. Sell Loot: Delete a specific node from the chain.
// Logic: Standard Linked List deletion (handle Head case vs Middle case).
// CRITICAL: You must FREE the magicEffect string first, then FREE the node.
int sellLoot(LootTable table, char *name) {
    // TODO:
    // 1. Calculate hash.
    int loc = hash(name);
    // 2. Traverse list to find node AND keep track of 'prev' node.
    LootNode* curr = table[loc];
    LootNode* prev = NULL;
    // 3. Unlink node.
    // 4. free(node->magicEffect); free(node);
    // Return 1 if deleted, 0 if not found.
    
    while(curr != NULL && strcmp(curr->name, name) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL) return 0;

    LootNode* toDelete = curr;
    if(prev == NULL) {
        table[loc] = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(toDelete);
    return 1;
}

int main() {
    LootTable myChest;
    initTable(myChest);

    printf("--- DUNGEON LOOT TRACKER ---\n");

    // TEST 1: Adding Items (Dynamic Allocation)
    // Note: Assuming TABLE_SIZE 5, some of these might collide.
    printf("\n[1] Storing Loot...\n");
    addLoot(myChest, "Excalibur", "Shines with holy light");
    addLoot(myChest, "RustyDagger", "Might give you tetanus");
    addLoot(myChest, "DragonEgg", "Warm to the touch"); 
    // Let's force a collision (Depends on hash, but conceptually):
    addLoot(myChest, "Bone", "Just a bone"); 

    printTable(myChest);

    // TEST 2: Retrieval
    printf("\n[2] Identifying 'Excalibur'...\n");
    char *desc = checkLoot(myChest, "Excalibur");
    printf(">> Description: %s\n", desc);

    // TEST 3: Deletion (Memory Management)
    printf("\n[3] Selling 'RustyDagger'...\n");
    if (sellLoot(myChest, "RustyDagger")) {
        printf(">> Sold 'RustyDagger'. Memory freed.\n");
    } else {
        printf(">> Item not found.\n");
    }

    printf("\n[4] Selling 'NonExistentItem'...\n");
    if (!sellLoot(myChest, "GhostOrb")) {
        printf(">> Correctly failed to sell missing item.\n");
    }

    printTable(myChest);
    // 'RustyDagger' should be gone. Others remain.

    return 0;
}


