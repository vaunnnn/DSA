#include <stdio.h>
#include <stdlib.h>
#define ROOT_NODE -1
#define INVALID_NODE -2

typedef struct ChildNode {
    int childIndex;
    struct ChildNode* next;
} ChildNode;

typedef struct {
    int rootIndex;
    ChildNode** children;
} Ree;

int* createTree(int n );
int* initTree(int* tree, int n);
int* addParent(int* tree, int child, int parent);
int* addRoot(int* tree, int index);
int* removeParent(int* tree, int child);
int left(int* tree, int n);
int right(int* tree, int n);
void displayTree(int* tree, int n);

Ree* initTreeList(Ree* T, int n);
void makeRoot(Ree* T, int root);
ChildNode* createNode(int child);
void addChild(Ree* T, int parent, int child);
void arrayToListTree(int* tree, Ree* T, int n);
void displayListTree(Ree* T, int n );

int main () {

    int n = 5;
    int* Tree = createTree(n);
    Tree = initTree(Tree, n);

    Tree = addRoot(Tree, 2);
    Tree = addParent(Tree, 0, 2);
    Tree = addParent(Tree, 1, 2);

    
    Tree = addParent(Tree, 3, 1);
    displayTree(Tree, n);

    int leftMost = left(Tree, n);
    printf("Leftmost Node: %d\n", leftMost);

    int rightMost = right(Tree, n);
    printf("Rightmost Node: %d\n", rightMost);

    Ree* T = NULL;
    T = initTreeList(T, n);
    arrayToListTree(Tree, T, n);
    displayListTree(T, n);

    printf("Root Node: %d\n", T->rootIndex);

    return 0;
}

int* createTree(int n) {
    int* tree = (int*)malloc(sizeof(int) * n);
    return tree;
}

int* initTree(int* tree, int n) {
    for(int i = 0; i < n; i++) {
        tree[i] = INVALID_NODE;
    }
    return tree;
}

int* addRoot(int* tree, int index) {
    tree[index] = ROOT_NODE;
    return tree;
}

int* addParent(int* tree, int child, int parent) {
    if(tree[child] == ROOT_NODE) return NULL;

    tree[child] = parent;  
    return tree;
}

int* removeParent(int* tree, int child) {
    if(tree[child] == ROOT_NODE) return NULL;

    tree[child] = INVALID_NODE;
    return tree;
}

int left(int* tree, int n) {
    if(tree[n] == ROOT_NODE) return ROOT_NODE;

    for(int i = 0; i < n; i++) {
        int isParent = 0;
        for(int j = 0; j < n; j++) {
            if(tree[j] == i) {
                isParent = 1;
            }
        }
        if(!isParent) return i;
    }
    return INVALID_NODE;
}
int right(int* tree, int n) {
    if(tree[n] == ROOT_NODE) return ROOT_NODE;
    for(int i = n - 1; i >= 0; i--) {
        int isParent = 0;
        for(int j = n - 1; j >= 0; j--) {

            if(tree[j] == i) isParent = 1;
        }
        if(!isParent) return i;
    }
    return INVALID_NODE;
}

Ree* initTreeList(Ree* T, int n) {
    T = (Ree*)malloc(sizeof(Ree));
    (T)->children = (ChildNode**)malloc(sizeof(ChildNode*) * n);
    
    for(int i = 0; i < n; i++) {
        (T)->children[i] = NULL;
    }
    return T;
}
void makeRoot(Ree* T, int root) {
    (T)->rootIndex = root;
}

ChildNode* createNode(int child) {
    ChildNode* newNode = (ChildNode*)malloc(sizeof(ChildNode));
    newNode->childIndex = child;
    newNode->next = NULL;
    return newNode;
}

void addChild(Ree* T, int parent, int child) {
    ChildNode* newNode = createNode(child);
    newNode->next = T->children[parent];
    (T)->children[parent] = newNode;
}

void arrayToListTree(int* tree, Ree* T, int n) {
    
    for(int i = 0; i < n; i++) {

        if(tree[i] == INVALID_NODE) continue; 
        if(tree[i] == ROOT_NODE) {
            makeRoot(T, i);
            continue;
        }
        addChild(T, tree[i], i);
    }

}

void displayTree(int* tree, int n){
    printf("---Tree Array Representation---\n");
    printf("Index [Child] | Parent\n");
    printf("----------------------\n");
    for(int i = 0; i < n; i++) {
        if(tree[i] == ROOT_NODE) {
            printf("%13d | ROOT\n", i);
        } else if (tree[i] == INVALID_NODE) {
            printf("%13d | (Uninitialized)\n", i); 
        } else {
            printf("%13d | %d\n", i, tree[i]);
        }
    }
}

void displayListTree(Ree* T, int n){
    printf("---Tree Children List Representation---\n");
    printf("Root Index: %d\n", T->rootIndex);
    printf("Parent Index | Children List\n");
    printf("----------------------\n");
    for(int i = 0; i < n; i++) {
        printf("%12d | ", i);
        ChildNode* curr = T->children[i];
        if(curr == NULL) {
            printf("(None)\n");
        } else {
            while (curr != NULL) {
                printf("%d -> ", curr->childIndex);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}