#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int count;
} List;

typedef struct {
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main() {

    Queue* q = initialize();

    printf("Enqueue 10, 20, 30\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);

    printf("Front: %d\n", front(q));

    printf("Dequeue: %d\n", dequeue(q));
    display(q);

    printf("Enqueue 40, 50\n");
    enqueue(q, 40);
    enqueue(q, 50);
    display(q);

    printf("Dequeue: %d\n", dequeue(q));
    display(q);

    printf("Dequeue all remaining elements...\n");
    while(q->list.count > 0) {
        printf("Removed %d\n", dequeue(q));
        display(q);
    }

    printf("Try dequeue on empty queue:\n");
    dequeue(q);



    return 0;
}

Queue* initialize() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));

    Q->list.count = 0;
    Q->front = -1;
    Q->rear = -1;
    
    return Q;
}

void enqueue(Queue* q, int value) {

    if(q->list.count == MAX) {
        printf("Queue is full\n");
        return;
    }

    if(q->list.count == 0) {
        q->front = 0;
        q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX; //1 + 1 % 10
    }

    q->list.items[q->rear] = value;
    q->list.count++;
    

}

int dequeue(Queue* q) {

    if(q->list.count == 0) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->list.items[q->front];
    q->front = (q->front + 1) % MAX;
    q->list.count--;

    if(q->list.count == 0) {
        q->front = -1;
        q->rear = -1;
    } 

    return value;

}
int front(Queue* q) {
    if(q->list.count == 0) {
        printf("Queue is empty\n");
        return -1;
    }

    return q->list.items[q->front];
}


void display(Queue* q) {
    if(q->list.count == 0) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");
    for(int i = 0; i < q->list.count; i++) {
        int index = (q->front + i) % MAX;
        printf("%d -> ", q->list.items[index]);
    }
    printf("NULL\n");
}