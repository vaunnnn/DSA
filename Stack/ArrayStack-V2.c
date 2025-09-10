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

    printf("Pushing values: 10, 20, 30\n");
    push(myStack, 10);
    push(myStack, 20);
    push(myStack, 30);
    display(myStack);

    printf("Peek top element: %d\n", peek(myStack));

    printf("Pop element: %d\n", pop(myStack));
    display(myStack);

    printf("Pop element: %d\n", pop(myStack));
    display(myStack);

    printf("Pop element: %d\n", pop(myStack));
    display(myStack);

    printf("Trying to pop from empty stack: %d\n", pop(myStack));

    free(myStack);

    return 0;
}

Stack* initialize() {
    Stack *S = (Stack*)malloc(sizeof(Stack));

    S->top = MAX - 1;
    return S;
}

void push(Stack* s, int value) {
    if(s->top == -1) return;

    s->items[(s->top)--] = value;
}

int pop(Stack* s) {
    if(s->top == MAX - 1) return -1;

    int currentTop = s->items[++(s->top)];
}

int peek(Stack* s) {
    if(s->top == MAX - 1) return -1;

    return s->items[s->top];
}

void display(Stack* s) {
    if(s->top == -1) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements (top -> bottom): ");
    for(int i = MAX - 1; i > s->top; i--) {
        printf("[%d] ", s->items[i]);
    }
    printf("\n");
}
