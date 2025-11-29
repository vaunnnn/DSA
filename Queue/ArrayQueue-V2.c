#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main() {
    Queue* q = initialize();

    printf("=== Enqueueing elements ===\n");
    for (int i = 1; i <= 5; i++) {
        enqueue(q, i * 10);
        display(q);
        printf("\n");
    }

    printf("\n=== Dequeue two elements ===\n");
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q);
    printf("\n");

    printf("\n=== Wraparound test ===\n");
    enqueue(q, 60);
    enqueue(q, 70);
    display(q);
    printf("\n");

    printf("\n=== Peek front ===\n");
    printf("Front element: %d\n", front(q));

    printf("\n=== Dequeue all ===\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
        display(q);
        printf("\n");
    }

    free(q);
    return 0;
}


Queue* initialize() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    
    q->front = 1;
    q->rear = 0;
    return q;
}

bool isEmpty(Queue* q) {
    if(q->front == (q->rear + 1) % MAX) return true;

    return false;
}

bool isFull(Queue* q) {
    if(q->front == (q->rear + 2) % MAX) return true;

    return false;
}

void enqueue(Queue* q, int value) {
    if(isFull(q)) {
        printf("Queue is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }

    int val = q->items[q->front];
    q->front = (q->front + 1) % MAX;
    return val;
}

int front(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty.\n");
        return -1;
    }
    return q->items[q->front];
}

void display(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    for(int i = q->front; i != (q->rear + 1) % MAX; i = (i + 1) % MAX) {
        printf("%d -> ", q->items[i]);
    }
}

