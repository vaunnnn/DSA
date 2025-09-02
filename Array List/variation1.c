#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} List;

List initList(List L) {
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int pos) {
    if (L.count == MAX) {
        printf("List is full!\n");
        return L;
    }
    if (pos < 0 || pos > L.count) { 
        printf("Invalid position!\n");
        return L;
    }

    for (int i = L.count; i > pos; i--) {
        L.elem[i] = L.elem[i - 1];
    }

    L.elem[pos] = data;
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
            L.elem[i] = L.elem[i + 1];
        }
        L.count--;
    }

    return L;
}

int locate(List L, int data) {
    int indexFound;
    int flag = 0;

    for(int i = 0; i < L.count; i++) {
        if(data == L.elem[i]) {
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
    if (L.count == MAX) {
        printf("List is full!\n");
        return L;
    }

    int pos = 0;
    while (pos < L.count && L.elem[pos] < data) {
        pos++;
    }

    return insertPos(L, data, pos);
}


void displayList(List L) {
    for(int i = 0; i < L.count; i++) {
        printf("[%d], ", L.elem[i]);
    }
}

int main() {
    List L;
    L = initList(L);

    L = insertPos(L, 10, 0);
    L = insertPos(L, 20, 1);
    L = insertPos(L, 30, 2);
    L = insertSorted(L, 15);
    L = deletePos(L, 0);
    L = insertSorted(L, 10);
    int indexNumber = locate(L, 10);

    if(indexNumber != -1) {
        printf("\nNumber found at Index: %d\n", indexNumber);
    } else {
        printf("\nNumber not found in the list\n");
    }

    displayList(L);

    return 0;
}