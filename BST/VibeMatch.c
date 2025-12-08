#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SongNode {
    int bpm;             // The key (Unique ID)
    char title[30];
    struct SongNode *left;
    struct SongNode *right;
} SongNode;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

SongNode* createNode(int bpm, char *title) {
    SongNode *newNode = (SongNode*)malloc(sizeof(SongNode));
    newNode->bpm = bpm;
    strcpy(newNode->title, title);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Visualizes the playlist sorted (In-Order Traversal)
void printPlaylist(SongNode *root) {
    if (root != NULL) {
        printPlaylist(root->left);
        printf("BPM: %d | Title: %s\n", root->bpm, root->title);
        printPlaylist(root->right);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Insert Track: Standard BST Insertion
// Recursively (or iteratively) place the new song based on BPM.
// Return the (possibly new) root of the tree.
SongNode* insertTrack(SongNode *root, int bpm, char *title) {
    // TODO:
    // If root is NULL, return createNode.
    // If bpm < root->bpm, go left.
    // If bpm > root->bpm, go right.
    // Return root.

    if(root == NULL) {
        return createNode(bpm, title);
    }

    if(bpm < root->bpm) {
        root->left = insertTrack(root->left, bpm, title);
    } else if (bpm > root->bpm) {
        root->right = insertTrack(root->right, bpm, title);
    }

    return root;
}

// 2. Find Track: Search for a specific BPM
// Return the Node if found, or NULL if it doesn't exist.
SongNode* findTrack(SongNode *root, int targetBPM) {
    // TODO: Standard BST search logic.

    if(root == NULL) return NULL;

    SongNode* curr = root;

    while(curr != NULL) {
        if(curr->bpm == targetBPM) {
            return curr;
        }
        if(targetBPM < curr->bpm) {
            curr = curr->left;
        } else if (targetBPM > curr->bpm) {
            curr = curr->right;
        }
    }
    return NULL;
}

// 3. Logic Check: "Energy Boost" (Find Successor)
// Find the song that is the "closest step up" from the currentBPM.
// Logic: You want the smallest BPM in the tree that is STRICTLY GREATER than currentBPM.
// Return that Node, or NULL if no higher song exists.
SongNode* getEnergyBoost(SongNode *root, int currentBPM) {
    // TODO:
    // Traverse the tree.
    // If node->bpm <= currentBPM: We need higher, go Right.
    // If node->bpm > currentBPM: This is a candidate! Save it, but try going Left
    //    to see if there is a tighter match (a smaller BPM that is still > current).
    SongNode* node = root;
    while(node != NULL) {
        if(node->bpm <= currentBPM) {
            node = node->right;
        } else if (node->bpm > currentBPM) {
            SongNode* curr = node;
            node = node->left;
            if (node->bpm < curr->bpm) {
                curr = node;
            }
            return curr;
        }
    }


    return NULL;
}

int main() {
    SongNode *playlist = NULL;

    printf("--- VIBEMATCH SYSTEM LOADING ---\n");

    // TEST 1: Building the Playlist
    // We insert in a specific order to create a nice tree structure.
    printf("\n[1] Importing Tracks...\n");
    playlist = insertTrack(playlist, 128, "Techno King");  // Root
    insertTrack(playlist, 120, "Deep House Vibes");
    insertTrack(playlist, 140, "Hardstyle Hero");
    insertTrack(playlist, 130, "Trance Anthem");
    insertTrack(playlist, 125, "Disco Groove");
    insertTrack(playlist, 150, "Speedcore Fury");
    
    printf(">> Current Sorted Playlist:\n");
    printPlaylist(playlist);

    // TEST 2: Search
    printf("\n[2] Checking Request for 140 BPM...\n");
    SongNode *found = findTrack(playlist, 140);
    if (found) printf("MATCH FOUND: %s\n", found->title);
    else printf("No track matches that BPM.\n");

    // TEST 3: The Energy Boost (Logic Check)
    // Scenario: Currently playing 128 BPM. We want the next step up.
    // 120, 125 are too slow.
    // 130, 140, 150 are faster.
    // 130 is the closest step up.
    
    printf("\n[3] Calculating Energy Boost (Next track > 128 BPM)...\n");
    SongNode *nextUp = getEnergyBoost(playlist, 128);
    
    if (nextUp) {
        printf("RECOMMENDATION: Transition to %s (%d BPM)\n", nextUp->title, nextUp->bpm);
    } else {
        printf("WARNING: No higher energy tracks available!\n");
    }
    // Expected: Trance Anthem (130 BPM)

    // TEST 4: Edge Case (Maximum Energy)
    // Currently playing 150. There is nothing higher.
    printf("\n[4] Calculating Energy Boost (Next track > 150 BPM)...\n");
    SongNode *maxOut = getEnergyBoost(playlist, 150);
    
    if (maxOut) {
        printf("RECOMMENDATION: Transition to %s (%d BPM)\n", maxOut->title, maxOut->bpm);
    } else {
        printf("WARNING: Maximum Energy Reached! No tracks available.\n");
    }
    // Expected: Warning

    return 0;
}
