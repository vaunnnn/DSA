#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front; // points to the front of the queue
    Node* rear;  // points to the rear of the queue
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    Queue* q = initialize();

    printf("=== Enqueueing elements ===\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);

    printf("\n=== Dequeueing two elements ===\n");
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    printf("\n=== Enqueue more ===\n");
    enqueue(q, 40);
    enqueue(q, 50);
    enqueue(q, 60);
    display(q);

    printf("\n=== Peek front ===\n");
    printf("Front element: %d\n", front(q));

    printf("\n=== Dequeue everything ===\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
        display(q);
    }

    printf("\nFinal state:\n");
    display(q);

    free(q); // cleanup
    return 0;
}

Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;

    return q;
}

bool isFull(Queue* q) {
    return false;
}

bool isEmpty(Queue* q) {
    if(q->front == NULL) return true;

    return false;
}

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;

    if(isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }

    Node* temp = q->front;
    int val = temp->data;
    q->front = temp->next;

    if(isEmpty(q)) {
        q->rear = NULL;
    }

    free(temp);
    return val;
}

int front(Queue* q) {
    if(q->front == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }

    return q->front->data;
}
void display(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    Node* temp = q->front;
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL \n");
}