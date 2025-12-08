#include <stdio.h>
#include <stdbool.h>

// --- DEFINITIONS ---
typedef unsigned int Potion;

// Ingredient Bit Definitions
#define TOADSTOOL   (1 << 0) // 1
#define LEAD        (1 << 1) // 2
#define SULFUR      (1 << 2) // 4
#define ARSENIC     (1 << 3) // 8
#define MERCURY     (1 << 4) // 16
#define GOLD_DUST   (1 << 5) // 32

// A Mask representing all dangerous ingredients (Arsenic | Mercury | Toadstool)
#define TOXIC_MASK  (ARSENIC | MERCURY | TOADSTOOL) 

// --- HELPER FUNCTION ---
void analyzeCauldron(Potion p) {
    printf("Cauldron Content (Binary): ");
    for (int i = 5; i >= 0; i--) {
        printf("%d", (p >> i) & 1);
    }
    printf(" (Decimal: %u)\n", p);
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Infuse: Add an ingredient to the mix.
// Operation: Use OR logic.
void infuseIngredient(Potion *p, unsigned int ingredientFlag) {
    // TODO: Set the bit corresponding to 'ingredientFlag' to 1.
        *p = *p | ingredientFlag;
}

// 2. Purify: Remove ALL ingredients listed in the TOXIC_MASK.
// Operation: You want to KEEP everything that is NOT toxic.
// Hint: Use AND (&) combined with the NOT (~) operator on the mask.
void purifyPotion(Potion *p) {
    // TODO: Clear bits 0, 3, and 4 (The TOXIC_MASK bits) simultaneously.

    *p = *p & ~TOXIC_MASK;
}

// 3. Transmute: Check the reaction logic.
// Returns: 1 (Perfect), -1 (Explosion), 0 (Sludge)
int checkReaction(Potion p) {
    // TODO:
    // A. If MERCURY AND SULFUR are both ON -> Return -1.
    // B. If GOLD_DUST is ON AND LEAD is OFF -> Return 1.
    // C. Else -> Return 0. 
    unsigned int mercury = (p & MERCURY) != 0;
    unsigned int sulfur = (p & SULFUR) != 0;
    unsigned int gold   = (p & GOLD_DUST) != 0;
    unsigned int lead   = (p & LEAD) != 0;

    if(mercury && sulfur) {
        return -1;
    } 

    if(gold && !lead) {
        return 1;
    }

    return 0;
}

int main() {
    Potion cauldron = 0;
    
    printf("--- ALCHEMY LAB 101 ---\n");

    // TEST 1: Basic Infusion
    printf("\n[1] Adding Sulfur and Mercury...\n");
    infuseIngredient(&cauldron, SULFUR);
    infuseIngredient(&cauldron, MERCURY);
    analyzeCauldron(cauldron); 
    // Expected: 010100 (Decimal 20)

    // TEST 2: Danger Check
    printf("\n[2] Checking Reaction...\n");
    int result = checkReaction(cauldron);
    if (result == -1) printf(">> RESULT: BOOM! Explosion detected.\n");
    else printf(">> RESULT: Stable.\n");
    // Expected: BOOM!

    // TEST 3: Complex Clearing (Masking)
    printf("\n[3] Adding Arsenic, Toadstool, and Gold Dust, then Purifying...\n");
    infuseIngredient(&cauldron, ARSENIC);
    infuseIngredient(&cauldron, TOADSTOOL);
    infuseIngredient(&cauldron, GOLD_DUST);
    printf("Before Purify: "); analyzeCauldron(cauldron);
    
    purifyPotion(&cauldron); // Should remove Mercury, Arsenic, Toadstool
    printf("After Purify:  "); analyzeCauldron(cauldron);
    // Expected: Should retain Sulfur (4) and Gold Dust (32). 
    // Mercury(16), Arsenic(8), Toadstool(1) should be gone.
    // Result binary: 100100 (36)

    // TEST 4: Success Logic
    printf("\n[4] Checking Final Product...\n");
    // Current state: Gold Dust is ON. Lead is OFF. Sulfur is ON.
    // Logic: Gold ON + Lead OFF = Perfect.
    result = checkReaction(cauldron);
    if (result == 1) printf(">> RESULT: PERFECT ELIXIR! You passed.\n");
    else printf(">> RESULT: Unstable Sludge.\n");

    return 0;
}
