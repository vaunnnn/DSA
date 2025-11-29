#include <stdio.h>
#include <stdbool.h>
#define ACTION_SIZE 30

typedef struct {
    char action[ACTION_SIZE];
    char content[ACTION_SIZE];
} Action;

typedef struct StackNode{
    Action act;
    struct StackNode* next;
} StackNode, *Stack;

typedef struct {
    Stack top;
    int count;
} ActionStack;

int main() {

    return 0;
}