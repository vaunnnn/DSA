#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field: 8;
} Set;

void initialize(Set *set);
void insert(Set *set, int element);
void delete(Set *set, int element);
bool find(Set set, int element);
Set unionSet(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(unsigned char set);

int main() {
    Set A, B, C;

    // Initialize both sets
    initialize(&A);
    initialize(&B);

    // Insert elements into A: {0, 4, 5}
    insert(&A, 0);
    insert(&A, 4);
    insert(&A, 5);
    printf("A = ");
    display(A.field);

    // Insert elements into B: {2, 5}
    insert(&B, 2);
    insert(&B, 5);
    printf("B = ");
    display(B.field);

    // Union of A and B
    C = unionSet(A, B);
    printf("Union = ");
    display(C.field);

    // Intersection of A and B
    C = intersection(A, B);
    printf("Intersection = ");
    display(C.field);

    // Difference of A and B (A - B)
    C = difference(A, B);
    printf("Difference = ");
    display(C.field);

    // Delete element 5 from A
    delete(&A, 5);
    printf("A after deleting 5 = ");
    display(A.field);

    // Test the find function
    if(find(A, 4))
        printf("Element 4 is in A ✅\n");
    else
        printf("Element 4 is not in A ❌\n");

    if(find(A, 5))
        printf("Element 5 is in A ✅\n");
    else
        printf("Element 5 is not in A ❌\n");

    return 0;

}

void initialize(Set *set) { 
    set->field = 0;
}

void insert(Set *set, int element) {
    if(element >= 0 && element <= 7) {
        unsigned int mask = 1 << element;
        set->field = set->field | mask;
    }
}

void delete(Set *set, int element) {
    if(element >= 0 && element <= 7) {
        unsigned int mask = 1 << element;
        mask = ~mask;
        set->field = set->field & mask;
    }
}

bool find(Set set, int element) { 
    unsigned int mask = 1 << element;
    if(set.field & mask) {
        return true;
    }
    return false;
}

Set unionSet(Set A, Set B) {
    Set C;
    C.field = A.field | B.field;
    return C;
}

Set intersection(Set A, Set B) {
    Set result;
    result.field = A.field & B.field;
    return result;
}

Set difference(Set A, Set B) {
    Set result;
    result.field = A.field & ~B.field;
    return result;
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