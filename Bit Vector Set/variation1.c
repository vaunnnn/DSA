#include <stdio.h>
#include <stdbool.h>

void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void delete(unsigned char *set, int element);
bool find(unsigned char set, int element);
unsigned char unionSet(unsigned char A, unsigned char B);
unsigned char intersection(unsigned char A, unsigned char B);
unsigned char difference(unsigned char A, unsigned char B);
void display(unsigned char set);

int main() {
    unsigned char A, B, C;
    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 6);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);

    printf("Set A: ");
    display(A);
    printf("Set B: ");
    display(B);

    C = unionSet(A, B);
    printf("Union: ");
    display(C);

    C = intersection(A, B);
    printf("Intersection: ");
    display(C);

    C = difference(A, B);
    printf("Difference (A - B): ");
    display(C);

    printf("Find 6 in A: %s\n", find(A, 6) ? "Yes" : "No");
    printf("Find 3 in A: %s\n", find(A, 3) ? "Yes" : "No");

    delete(&A, 6);
    printf("After deleting 6 from A: ");
    display(A);


}


void initialize(unsigned char *set) {
    *set = 0;
}

void insert(unsigned char *set, int element) {
    if(element >= 0 && element <= 7) {
        unsigned int mask = 1 << element;
        *set = *set | mask;
    }
}

void delete(unsigned char *set, int element) {
    if(element >= 0 && element <= 7) {
        unsigned int mask = 1 << element; 
        mask = ~mask;
        *set = *set & mask; 
    }
}



bool find(unsigned char set, int element) {
    unsigned int mask = 1 << element;
    if(mask & set) {
        return true;
    }
    return false;
}

unsigned char unionSet(unsigned char A, unsigned char B) {
    return A | B;
}

unsigned char intersection(unsigned char A, unsigned char B) {
    return A & B;
}

unsigned char difference(unsigned char A, unsigned char B) {
    return A & ~B;
}

void display(unsigned char set) {
    printf("{ ");
    for(int i = 0; i < 8; i++) { 
        if(set & (1 << i)) {       
            printf("%d ", i);
        }
    }
    printf("}\n");
}