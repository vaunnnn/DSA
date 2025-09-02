#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct {
    int elem[MAX];
    int count;
} Etype, *EPtr;

void initList(EPtr L);
void insertPos(EPtr L, int data, int pos);
void deletePos(EPtr L, int pos);
int locate(EPtr L, int data);
int retrieve(EPtr L, int pos);
void insertSorted(EPtr L, int data);
void displayList(EPtr L);
void makeNULL(EPtr L);

int main() {
    EPtr L = (EPtr)malloc(sizeof(Etype));
    initList(L);

    insertPos(L, 10, 0);
    insertPos(L, 20, 1);
    insertPos(L, 30, 2);
    int a = retrieve(L, 2);
    printf("NUM %d\n\n", a);
    insertSorted(L, 15);
    deletePos(L, 3);
    deletePos(L, 0);
    displayList(L);
    makeNULL(L);
    return 0;
}

void initList(EPtr L) {
    L->count = 0;
}

void insertPos(EPtr L, int data, int pos) {
    if(L->count == MAX) {
        printf("List is full please try again");
        return;
    }

    if(pos < 0 || pos > L->count) {
        printf("Invalid position please try again");
        return;
    }

    for(int i = L->count; i > pos; i--) {
        L->elem[i] = L->elem[i - 1];
    }

    L->elem[pos] = data;
    L->count++;
}
void deletePos(EPtr L, int pos) {

    if(L->count == 0) {
        printf("List is empty please insert values");  
    }

    if(pos > L->count) {
        printf("Position invalid please try again");
    }

    if(pos == L->count) {
        L->count--;
    }

    if(pos <= L->count) {
        for(int i = pos; i < L->count; i++) {
            L->elem[i] = L->elem[i + 1];
        }
        L->count--;
    }
}
int locate(EPtr L, int data) {
    int indexFound;
    int flag = 0;

    for(int i = 0; i < L->count; i++) {
        if(L->elem[i] == data) {
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

int retrieve(EPtr L, int pos) {
    if(pos < 0 || pos > L->count) {
        printf("Invalid position");
        return -1;
    }

    return L->elem[pos];
    
}
void insertSorted(EPtr L, int data) {
    
    if (L->count == MAX) {
        printf("List is full!\n");
        return L;
    }

    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) {
        pos++;
    }

    return insertPos(L, data, pos);
}

void displayList(EPtr L) {
    for(int i = 0; i < L->count; i++) {
        printf("[%d], ", L->elem[i]);
    }
}

void makeNULL(EPtr L) {
    free(L);
}