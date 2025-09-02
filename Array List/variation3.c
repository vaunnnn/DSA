#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List initList(List L);
List insertPos(List L, int data, int pos);
List deletePos(List L, int pos);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);
List resize(List L);

int main() {
    List L;

    // Initialize
    printf("=== Initialize ===\n");
    L = initList(L);
    display(L);   // Expect: count=0, max=10

    // Insert at positions
    printf("\n=== Insert at positions ===\n");
    L = insertPos(L, 10, 0); // Insert 10 at pos 0
    L = insertPos(L, 20, 1); // Insert 20 at pos 1
    L = insertPos(L, 15, 1); // Insert 15 at pos 1, shifting 20 to the right
    L = insertPos(L, 5, 0);  // Insert 5 at start
    display(L);   // Expect: 5 10 15 20

    // Delete at positions
    printf("\n=== Delete at positions ===\n");
    L = deletePos(L, 0); // Delete first element (5)
    display(L);   // Expect: 10 15 20

    L = deletePos(L, 1); // Delete element at pos 1 (15)
    display(L);   // Expect: 10 20

    L = deletePos(L, 5); // Invalid delete
    display(L);   // Expect: still 10 20

    // Locate
    printf("\n=== Locate ===\n");
    int idx = locate(L, 20);
    printf("Locate 20 → %d\n", idx); // Expect: 1

    idx = locate(L, 99);
    printf("Locate 99 → %d\n", idx); // Expect: -1

    // Insert sorted
    printf("\n=== Insert Sorted ===\n");
    L = insertSorted(L, 12); // Goes between 10 and 20
    L = insertSorted(L, 18); // Goes before 20
    L = insertSorted(L, 2);  // Goes at start
    display(L);   // Expect: 2 10 12 18 20

    // Trigger resize
    printf("\n=== Trigger Resize ===\n");
    for (int i = 100; i < 115; i++) {
        L = insertPos(L, i, L.count); // Append at end
    }
    display(L);   // Expect: 2 10 12 18 20 100 101 ... 114
    printf("Current max capacity: %d\n", L.max); // Expect: 20 (doubled)

    return 0;
}


List initList(List L) {
    L.elemPtr = (int*)malloc(LENGTH * sizeof(int));
    L.count = 0;
    L.max = LENGTH;

    return L;
}

List insertPos(List L, int data, int pos) {

    if (L.count == L.max) {
        L = resize(L);
    }

    if (pos < 0 || pos > L.count) { 
        printf("Invalid position!\n");
        return L;
    }

    for(int i = L.count; i > pos; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[pos] = data;
    L.count++;
    return L;
    
}

List deletePos(List L, int pos) {

    if(L.count == 0) {
        printf("List is empty please insert values");
    }

    if(pos > L.count) {
        printf("Position invalid please try again");
    }

    if(pos == L.count) {
        L.count--;
    }

    if(pos <= L.count) {
        for(int i = pos; i < L.count; i++) {
            L.elemPtr[i] = L.elemPtr[i + 1];
        }
        L.count--;
    }

    return L;
}

int locate(List L, int data) {
    int indexFound;
    int flag = 0;

    for(int i = 0; i < L.count; i++) {
        if(data == L.elemPtr[i]) {
            indexFound = i;
            flag = 1;
            break;
        }
    }

    if(flag == 0) {
        return -1;
    } else {
        return indexFound;
    }
}

List insertSorted(List L, int data) {

    if(L.count == L.max) {
        L = resize(L);
    }
    
    int pos = 0;
    while (pos < L.count && L.elemPtr[pos] < data) {
        pos++;
    }

    return insertPos(L, data, pos);
}

void display(List L) {
    printf("List (count = %d, max = %d): ", L.count, L.max);
    for (int i = 0; i < L.count; i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("\n");
}

List resize(List L) {
    L.max *= 2;
    L.elemPtr = realloc(L.elemPtr, L.max * sizeof(int));
    return L;
}