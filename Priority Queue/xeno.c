#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 20

typedef struct {
    char speciesName[30];    // Static size
    char *containmentNote;   // DYNAMIC size (Requires malloc)
    int dangerRating;        // Priority Key (Higher = More Dangerous)
} Alien;

typedef struct {
    Alien *heap;             // Dynamic array of Aliens (or static if you prefer, but let's use a pointer to array)
    int count;
    int capacity;
} PriorityQueue;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initQueue(PriorityQueue *pq) {
    pq->count = 0;
    pq->capacity = MAX_CAPACITY;
    pq->heap = (Alien *)malloc(sizeof(Alien) * MAX_CAPACITY);
}

void printQueue(PriorityQueue *pq) {
    printf("--- SECTOR 4 STATUS (Count: %d) ---\n", pq->count);
    if (pq->count == 0) {
        printf("[Facility Empty]\n");
        return;
    }
    // Prints in array order (Level Order Traversal)
    for (int i = 0; i < pq->count; i++) {
        printf("[%d] %s (Danger: %d) | Note: %s\n", 
               i, pq->heap[i].speciesName, pq->heap[i].dangerRating, pq->heap[i].containmentNote);
    }
    printf("-----------------------------------\n");
}

void swap(Alien *a, Alien *b) {
    Alien temp = *a;
    *a = *b;
    *b = temp;
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Logic Helper: Sift Down (The Complex Logic)
// Used during extraction. Check the parent against its children.
// Swap with the LARGEST child if the heap property is violated.
// Repeat until the node is in the correct spot.
void siftDown(PriorityQueue *pq, int index) {
    // TODO:
    // 1. Identify left child (2*i + 1) and right child (2*i + 2).
    // 2. Find the largest among Root, Left, and Right.
    // 3. If Root is NOT the largest, swap with the largest child.
    // 4. Recursively (or iteratively) call siftDown on the new index.
    int max = index;
    int left = 2 * max + 1;
    int right = 2 * max + 2;

    if(left < pq->count && pq->heap[left].dangerRating > pq->heap[max].dangerRating) 
        max = left;

    if(right < pq->count && pq->heap[right].dangerRating > pq->heap[max].dangerRating)
        max = right;

    if(max != index) {
        swap(&pq->heap[max], &pq->heap[index]);
        siftDown(pq, max);
    }
}

void siftUp(PriorityQueue* pq, int index) {
    int parent = (index - 1) / 2;

    while(index != 0 && pq->heap[index].dangerRating > pq->heap[parent].dangerRating) {
        swap(&pq->heap[index], &pq->heap[parent]);
        siftUp(pq, parent);
    }
}

// 2. Admit Alien (Insert):
// Adds a new alien. Mallocs memory for the note.
// Ensures the most dangerous alien floats to the top (Sift Up logic).
// Returns 1 if successful, 0 if full.

Alien createNode(char* name, int danger, char* note) {
    Alien newNode;
    newNode.containmentNote = (char*)malloc(sizeof(char) * strlen(note) + 1);
    
    strcpy(newNode.speciesName, name);
    strcpy(newNode.containmentNote, note);
    newNode.dangerRating = danger;

    return newNode;
}

int admitAlien(PriorityQueue *pq, char *name, int danger, char *note) {
    if (pq->count >= pq->capacity) return 0;

    Alien newNode = createNode(name, danger, note);
    pq->heap[pq->count] = newNode;
    siftUp(pq, pq->count);
    pq->count++;

    return 1;
}

// 3. Process Alien (Extract Max):
// Removes the root (highest danger).
// Returns the Alien object (so the main function can free the memory later).
// If empty, return an Alien with dangerRating = -1.
Alien processAlien(PriorityQueue *pq) {
    Alien topAlien;
    if (pq->count == 0) {
        topAlien.dangerRating = -1;
        return topAlien;
    }

    topAlien = pq->heap[0];

    swap(&pq->heap[0], &pq->heap[pq->count - 1]);
    pq->count--;
    siftDown(pq, 0);
    
    return topAlien;
}

int main() {
    PriorityQueue sector4;
    initQueue(&sector4);

    printf("--- ALIEN CONTAINMENT PROTOCOL INITIATED ---\n");

    // TEST 1: Admitting Aliens (with Memory Allocation)
    printf("\n[1] Incoming Transfers...\n");
    
    // Normal Danger
    admitAlien(&sector4, "Gloop", 20, "Keep away from water");
    
    // High Danger - Should float up
    admitAlien(&sector4, "Xenomorph", 95, "Acid blood - Handle with care");
    
    // Medium Danger
    admitAlien(&sector4, "Martian", 50, "Allergic to country music");
    
    // Extreme Danger - Should become new Root
    admitAlien(&sector4, "Predator", 99, "Invisibility cloak active");

    printQueue(&sector4);
    // EXPECTED ORDER (roughly): 
    // Root: Predator (99)
    // Children: Xenomorph (95), Martian (50) ...

    // TEST 2: Processing (Extract Max)
    printf("\n[2] Processing Highest Threat...\n");
    Alien processed = processAlien(&sector4);
    
    if (processed.dangerRating != -1) {
        printf(">> PROCESSED: %s (Danger: %d)\n", processed.speciesName, processed.dangerRating);
        printf(">> NOTE: %s\n", processed.containmentNote);
        
        // CRITICAL: Free the memory we malloc'd in admitAlien!
        free(processed.containmentNote); 
        printf(">> MEMORY CLEARED for %s.\n", processed.speciesName);
    }
    
    printQueue(&sector4);
    // EXPECTED ROOT: Xenomorph (95) - (Next highest)

    // TEST 3: Heap Logic Check
    printf("\n[3] Processing Next Threat...\n");
    processed = processAlien(&sector4); // Should be Xenomorph
    printf(">> PROCESSED: %s (Danger: %d)\n", processed.speciesName, processed.dangerRating);
    free(processed.containmentNote);

    printQueue(&sector4);
    // EXPECTED ROOT: Martian (50)

    // Cleanup rest of heap (Optional, but good practice in C)
    // In a real exam, you'd write a cleanup function loop.
    
    return 0;
}
