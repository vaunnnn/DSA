#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int count;
} List;

List* initialize();
void empty(List *list);
void insertFirst(List *list, int data);
void insertLast(List *list, int data);
void insertPos(List *list, int data, int index);
void deleteStart(List *list);
void deleteLast(List *list);
void deletePos(List *list, int index);
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);

int main(){

    List* myList = initialize();

    printf("=== TESTING LINKED LIST FUNCTIONS ===\n");

    // Insert at beginning
    insertFirst(myList, 10);
    insertFirst(myList, 20);
    printf("After insertFirst (20, then 10): ");
    display(myList);

    // Insert at end
    insertLast(myList, 30);
    insertLast(myList, 40);
    printf("After insertLast (30, 40): ");
    display(myList);

    // Insert at position
    insertPos(myList, 25, 2); // insert 25 at index 2
    printf("After insertPos(25 at index 2): ");
    display(myList);

    // Retrieve element
    int val = retrieve(myList, 3);
    printf("Retrieve element at index 3: %d\n", val);

    // Delete from start
    deleteStart(myList);
    printf("After deleteStart: ");
    display(myList);

    // Delete from end
    deleteLast(myList);
    printf("After deleteLast: ");
    display(myList);

    // Delete at position
    deletePos(myList, 1);
    printf("After deletePos(index 1): ");
    display(myList);

    // Empty the list
    empty(myList);
    printf("After empty(): ");
    display(myList);



    return 0;
}

List* initialize() {
    List *L = (List*)malloc(sizeof(List));

    if(L == NULL) {
        return NULL;
    }

    L->head = NULL;
    L->count = 0;

    return L;        
}


void empty(List *list) {
    while(list->head != NULL) {
        Node* temp = list->head;
        list->head = temp->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}


void insertFirst(List *list, int data) {

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    newNode->next = list->head;
    list->head = newNode;
    list->count++;
}


void insertLast(List *list, int data) {

    if(list->head == NULL) return;
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node* curr = list->head;

    for(int i = 0; i < list->count - 1; i++) {
        curr = curr->next;
    }
    curr->next = newNode;

    list->count++;
}

void insertPos(List *list, int data, int index) {
    if(index > list->count) {
        return;
    }

    if(index == 0) {
        insertFirst(list, data);
        return;
    }

    if(index == list->count) { 
        insertLast(list, data);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;

    Node* curr = list->head;
    int count = 0;
    while(curr != NULL && count < index - 1) { // 4 - 1 == 3 count = 0
        curr = curr->next;
        count++;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    list->count++;
}

void deleteStart(List *list) {
    Node* curr = list->head;
    list->head = curr->next;
    free(curr);
    list->count--;
}

void deleteLast(List *list) {
    Node* deleteNode = list->head;
    for(int i = 1; i < list->count - 1; i++) { 
        deleteNode = deleteNode->next;
    }
    Node* temp = deleteNode->next;
    deleteNode->next = NULL;
    free(temp);
    list->count--;
}


void deletePos(List* L, int index) {

    if(index > L->count) return;

    if(index == 0) {
        deleteStart(L);
        return;
    }

    Node* curr = L->head;
    
    for(int i = 1; i < index; curr = curr->next, i++);

    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);
    L->count--;
}

int retrieve(List *list, int index) {
    if(index > list->count) return -1;

    Node* curr = list->head;
    for(int i = 0; i < index; i++, curr = curr->next){}; 

    return curr->data;
}

void display(List *list) {
    Node* curr = (*list).head;
    while(curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}