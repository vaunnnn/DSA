#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int items[MAX];
    int top;
} Stack;

Stack* initialize();
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);


int main() {

    Stack* myStack = initialize();

    printf("=== STACK TEST CASES ===\n\n");

    printf("Pushing values: 10, 20, 30\n");
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    display(myStack);

    printf("\n\nPeek top element: %d\n", peek(myStack));

    printf("\nPop element: %d\n", pop(myStack));
    display(myStack);

    printf("\n\nPop element: %d\n", pop(myStack));
    display(myStack);

    printf("\n\nPop element: %d\n", pop(myStack));
    display(myStack);

    printf("\n\nTrying to pop from empty stack: %d\n", pop(myStack));

    printf("\nPushing more values until stack is full...\n");
    for(int i = 1; i <= MAX; i++) {
        push(myStack, i*5);
    }
    display(myStack);

    printf("\n\nTrying to push when stack is full...\n");
    push(myStack, 999); 
    display(myStack);

    free(myStack);

    return 0;
}

Stack* initialize() {
    Stack *S = (Stack*)malloc(sizeof(Stack));

    S->top = -1;
    return S;
}

void push(Stack* s, int value) {
    if(s->top == MAX - 1) return;

    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    if(s->top == -1) return -1;

    int currentTop = s->items[s->top];
    s->top--;
    return currentTop;
}

int peek(Stack* s) {
    if(s->top == -1) return -1;

    return s->items[s->top];
}

void display(Stack* s) {
    if(s->top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top -> bottom): ");
    for(int i = s->top; i >= 0; i--) {
        printf("[%d] ", s->items[i]);
    }
    printf("\n");
}
