#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* initializeStack();   
bool isEmpty(Stack* s);      
void push(Stack* s, int val);
int pop(Stack* s);
int peek(Stack* s);         
void display(Stack* s);     
void freeStack(Stack* s); 


int main() {
    Stack* s = initializeStack();

    // Test 1: Check empty stack
    printf("Is stack empty? %s\n", isEmpty(s) ? "Yes" : "No");

    // Test 2: Push elements
    push(s, 10);
    push(s, 20);
    push(s, 30);
    printf("After pushing 10, 20, 30:\n");
    display(s);

    // Test 3: Peek top element
    printf("Peek top: %d\n", peek(s)); // should be 30

    // Test 4: Pop one element
    printf("Popped: %d\n", pop(s)); // should be 30
    printf("Stack after pop:\n");
    display(s);

    // Test 5: Pop all elements
    printf("Popped: %d\n", pop(s)); // should be 20
    printf("Popped: %d\n", pop(s)); // should be 10
    printf("Is stack empty now? %s\n", isEmpty(s) ? "Yes" : "No");

    // Test 6: Pop from empty stack
    printf("Popped: %d\n", pop(s)); // should print "Stack is empty"

    // Cleanup
    freeStack(s);
    free(s);

    return 0;
}


Stack* initializeStack() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    
    return s;
}

bool isEmpty(Stack* s) {
    if(s->top == NULL) return true;
    
    return false;
}

void push(Stack* s, int val) {
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if(isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    Node* temp = s->top;
    s->top = temp->next;
    int val = temp->data;
    free(temp);
    
    return val;
}
int peek(Stack* s) {
    if(s->top == NULL) return -1;
    
    return s->top->data;
}
void display(Stack* s){
    Node* temp = s->top;
    printf("\n--- Stack ---\n");
    
    if(temp == NULL) {
        printf("Stack is empty");
        return;
    }
    
    while(temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}
void freeStack(Stack* s) {
    
    while(s->top != NULL) {
        Node* toDelete = s->top;
        s->top = toDelete->next;
        free(toDelete);
    }
    
}

bool isValidOrdering(Stack* s1, Stack* s2, int size1, int size2) {
    if(size1 != size2) return false;
    
    while(!isEmpty(s1) && !isEmpty(s2)) {
        int temp1 = peek(s1);
        int temp2 = peek(s2);
        
        if(temp1 == temp2) {
            pop(s1);
            pop(s2);
        } else {
            pop(s1);
        }
    }
    
    return isEmpty(s2);
}