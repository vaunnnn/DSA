#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// The unit of work
typedef struct {
    int id;                 // Unique Task ID
    char description[50];   // e.g., "Hull Breach Sector 7"
    int severity;           // Priority Level (1-100). Higher = More Critical.
} RepairTask;

// The Priority Queue
typedef struct {
    RepairTask tasks[MAX_SIZE];
    int count;              // Current number of tasks in heap
} DroneQueue;

void sift_up(DroneQueue* q, int child_idx);
void sift_down(DroneQueue* q, int parent_idx);

// Core operations
void schedule_repair(DroneQueue* q, int id, char* desc, int sev);
RepairTask perform_repair(DroneQueue* q);
void escalate_sector_priority(DroneQueue* q, char* sector_name, int boost_amount);

// Queue utilities
void init_queue(DroneQueue* q);
int is_empty(DroneQueue* q);
int is_full(DroneQueue* q);
void swap(RepairTask* a, RepairTask* b);
void print_queue(DroneQueue* q);


// main.c
// Assume the structs and function prototypes are included here

int main() {
    DroneQueue stationQueue;
    init_queue(&stationQueue);

    printf("--- SYSTEM STATUS: NORMAL ---\n");
    
    // 1. Test Enqueue (sift_up logic)
    // Format: schedule_repair(&queue, ID, Description, Severity)
    schedule_repair(&stationQueue, 101, "Cafeteria Microwave Broken", 10);
    schedule_repair(&stationQueue, 102, "Oxygen Recycler Leak", 85);
    schedule_repair(&stationQueue, 103, "Solar Panel Misalignment", 60);
    schedule_repair(&stationQueue, 104, "Hull Vibration Sector 4", 40);
    schedule_repair(&stationQueue, 105, "Main Thruster Overheat", 95);

    printf("Queue after initial alerts (Should see Thruster or Oxygen at top):\n");
    print_queue(&stationQueue);

    // 2. Test The Logic Function (Escalate)
    printf("\n--- WARNING: SECTOR 4 CRITICAL FAILURE ---\n");
    printf("Escalating all 'Sector 4' tasks by +50 priority...\n");
    

    // This finds "Hull Vibration Sector 4" (severity 40) and boosts it to 90.
    // It must then fix the heap because 90 > 60 (Solar Panel) and 85 (Oxygen).
    escalate_sector_priority(&stationQueue, "Sector 4", 50);
    
    print_queue(&stationQueue);

    // 3. Test Dequeue (sift_down logic)
    printf("\n--- DEPLOYING DRONES (Processing Tasks) ---\n");
    
    while (!is_empty(&stationQueue)) {
        RepairTask current = perform_repair(&stationQueue);
        printf("Releasing Drone for Task %d: [%s] (Severity: %d)\n", 
               current.id, current.description, current.severity);
    }

    return 0;
}

// --- HELPER FUNCTIONS (ALREADY DONE FOR YOU) ---

void init_queue(DroneQueue* q) {
    q->count = 0;
}

int is_empty(DroneQueue* q) {
    return q->count == 0;
}

int is_full(DroneQueue* q) {
    return q->count == MAX_SIZE;
}

void swap(RepairTask* a, RepairTask* b) {
    RepairTask temp = *a;
    *a = *b;
    *b = temp;
}

// Visualizer for debugging
void print_queue(DroneQueue* q) {
    printf("Current Queue Status (%d tasks):\n", q->count);
    for(int i = 0; i < q->count; i++) {
        printf("  [%d] %s (Sev: %d)\n", i, q->tasks[i].description, q->tasks[i].severity);
    }
}

// --- STUDENT TO DO SECTION ---

// Moves a node UP if it is larger than its parent
// Used by: schedule_repair AND escalate_sector_priority
void sift_up(DroneQueue* q, int child_idx) {
    // 1. Calculate parent_idx = (child_idx - 1) / 2
    // 2. Loop while child > 0 and child's severity > parent's severity
    // 3. Swap and update indices
    int parent = (child_idx - 1) / 2;
    
    while(child_idx != 0 && q->tasks[child_idx].severity > q->tasks[parent].severity) {
        swap(&q->tasks[child_idx], &q->tasks[parent]);
        sift_up(q, parent);
    }
}

// Moves a node DOWN if it is smaller than its children
// Used by: perform_repair
void sift_down(DroneQueue* q, int parent_idx) {
    // 1. Calculate left_child = (2 * parent_idx) + 1
    // 2. Loop while left_child < q->count
    // 3. Find larger child (check if right_child exists and is > left_child)
    // 4. If parent < larger_child, swap. Else break.
    int largest = parent_idx;
    int left = 2 * largest + 1;
    int right = 2 * largest + 2;
    
    if(left < q->count && q->tasks[left].severity > q->tasks[largest].severity)
        largest = left;
        
    if(right < q->count && q->tasks[right].severity > q->tasks[largest].severity)
        largest = right;
        
    if(largest != parent_idx) {
        swap(&q->tasks[largest], &q->tasks[parent_idx]);
        sift_down(q, largest);
    }
        
}

void rebuildHeap(DroneQueue* q) {
    for(int i = q->count / 2 - 1; i >= 0; i--) {
        sift_down(q, i);
    }
}


/* TODO 1: schedule_repair
   Add a new task to the heap.
   1. Check if full.
   2. Insert at the end (q->tasks[q->count]).
   3. Increment count.
   4. "Bubble Up" (Sift Up) to restore Max-Heap property.
*/

RepairTask createNode(int id, char* desc, int sev) {
    RepairTask newNode;
    newNode.id = id;
    strcpy(newNode.description, desc);
    newNode.severity = sev;
    return newNode;
}

void schedule_repair(DroneQueue* q, int id, char* desc, int sev) {
    // YOUR CODE HERE
    if(is_full(q)) return;
    
    q->tasks[q->count] = createNode(id, desc, sev);
    sift_up(q, q->count);
    q->count++;
}

/* TODO 2: perform_repair
   Remove and return the highest priority task (root).
   1. Check if empty (return a dummy task or handle error).
   2. Store the root (index 0).
   3. Move the last element (index count-1) to the root.
   4. Decrement count.
   5. "Bubble Down" (Sift Down) to restore Max-Heap property.
*/  
RepairTask perform_repair(DroneQueue* q) {
    RepairTask dummy = {1, "Dummy", 0};
    if(is_empty(q)) return dummy;
    // YOUR CODE HERE
    
    RepairTask finishedTask = q->tasks[0];
    swap(&q->tasks[0], &q->tasks[q->count - 1]);
    q->count--;
    sift_down(q, 0);
    
    return finishedTask;
}

/* TODO 3: escalate_sector_priority (THE LOGIC CHALLENGE)
   The station sensors detected a localized crisis!
   
   1. Iterate through the ENTIRE array (0 to count-1).
   2. If a task's description contains the substring `sector_name` (use strstr):
      - Add `boost_amount` to its severity.
      - Because the severity INCREASED, the item might now be larger than its parent.
      - Perform a "Bubble Up" on this specific index to fix the heap order.
   
   NOTE: You do not need to Bubble Down, because we are only adding to the severity.
*/
void escalate_sector_priority(DroneQueue* q, char* sector_name, int boost_amount) {
    // YOUR CODE HERE
    for(int i = 0; i < q->count; i++) {
        if(strstr(q->tasks[i].description, sector_name)) {
            q->tasks[i].severity += boost_amount;
            sift_up(q, i);
        }
    }
}


