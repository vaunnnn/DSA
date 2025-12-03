#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node **adjList;
} Graph;

int** initializeMatrix(int n);
void addEdgeMatrix(int **matrix, int u, int v, int isDirected);
void removeEdgeMatrix(int **matrix, int u, int v, int isDirected);
int hasEdgeMatrix(int **matrix, int u, int v);
void printMatrix(int **matrix, int n);
void getNeighborsMatrix(int **matrix, int n, int u);
void freeMatrix(int **matrix, int n);

Graph *createGraph(int vertices);
Node *createNode(int vertex);

void addEdge(Graph *graph, int src, int dest, int isDirected);
void removeEdge(Graph *graph, int src, int dest, int isDirected);
int edgeExists(Graph* graph, int src, int dest);

void printGraph(Graph *graph);
void getNeighbors(Graph *graph, int vertex);

int hasEdge(Graph *graph, int src, int dest);
int degree(Graph *graph, int vertex);

void freeGraph(Graph *graph);

void matrixToList(Graph* graph, int** matrix, int n);

int main() {
    int n = 5;
    int** matrix = NULL;
    matrix = initializeMatrix(n);

    addEdgeMatrix(matrix, 1, 4, 1);
    addEdgeMatrix(matrix, 4, 3, 0);
    addEdgeMatrix(matrix, 4, 2, 1);
    addEdgeMatrix(matrix, 2, 3, 1);

    printMatrix(matrix, n);

    printf("\n====Turning Adjacency Matrix to Adjacency List====\n");

    Graph* graph = createGraph(n);

    matrixToList(graph, matrix, n);

    printGraph(graph);


    

    return 0;
}

int** initializeMatrix(int n) {
    int** matrix = (int**)malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
    }

    return matrix;
}

void addEdgeMatrix(int **matrix, int u, int v, int isDirected) {
    matrix[u][v] = 1;
    if(!isDirected) matrix[v][u] = 1;
}

void removeEdgeMatrix(int **matrix, int u, int v, int isDirected) {
    matrix[u][v] = 0;
    if(!isDirected) matrix[v][u] = 0;
}

int hasEdgeMatrix(int **matrix, int u, int v) {
    return matrix[u][v] == 1;
}
void printMatrix(int **matrix, int n) {
    printf("\n====Adjacency Matrix====\n   ");
    for(int i = 0; i < n; i++) {
        printf("%d ", i);
    }
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("%d: ", i);
        for(int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void getNeighborsMatrix(int **matrix, int n, int u) {
    printf("\n====Neighbors of Index: %d====\n", u);
    for(int i = 0; i < n; i++) {
        if(matrix[u][i] == 1) {
            printf("%d ", i);
        }
    }
}
void freeMatrix(int **matrix, int n) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

Graph *createGraph(int vertices) {
    Graph* list = (Graph*)malloc(sizeof(Graph));

    list->numVertices = vertices;
    list->adjList = (Node**)malloc(vertices * sizeof(Node*));
    for(int i = 0; i < vertices; i++) {
        list->adjList[i] = NULL;
    }
    // printf("HI\n");
    return list;
}
Node *createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int src, int dest, int isDirected) {

    if(edgeExists(graph, src, dest)) return;

    Node* newNode = createNode(dest);

    Node* temp = graph->adjList[src];

    if(temp == NULL) {
        graph->adjList[src] = newNode;
        return;
    }

    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

    if(!isDirected && !edgeExists(graph, src, dest)) {
        Node* newNode2 = createNode(src);

        temp = graph->adjList[dest];

        if(temp == NULL) {
            graph->adjList[src] = newNode;
            return;
        }
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode2;
    }
}

void removeEdge(Graph *graph, int src, int dest, int isDirected) {
    Node* curr = graph->adjList[src];
    Node* prev = NULL;

    while(curr != NULL && curr->vertex != dest) {
        curr = curr->next;
    }

    if(curr == NULL) return;

    if(prev = NULL) {
        graph->adjList[src] = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);
}

void printGraph(Graph *graph) {
    printf("\n====Adjacency List====\n");
    for(int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        Node* temp = graph->adjList[i];
        while(temp != NULL){
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void getNeighbors(Graph *graph, int vertex) {
    Node* temp = graph->adjList[vertex];

    while(temp != NULL) {
        printf("%d ->", temp->vertex);
        temp = temp->next;
    }
    printf("NULL\n");
}

int hasEdge(Graph *graph, int src, int dest) {
    Node* curr = graph->adjList[src];
    while(curr != NULL) {
        if(curr->vertex = dest) {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

int degree(Graph *graph, int vertex) {
    Node* temp = graph->adjList[vertex];
    int count = 0;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void freeGraph(Graph *graph) {
    for(int i = 0; i < graph->numVertices; i++) {
        Node* curr = graph->adjList[i];
        while(curr != NULL) {
            Node* toDel = curr;
            curr = toDel->next;
            free(toDel);            
        }
    }
    free(graph->adjList);
    free(graph);
}

int edgeExists(Graph* graph, int src, int dest) {
    Node* cur = graph->adjList[src];
    while (cur != NULL) {
        if (cur->vertex == dest) return 1;
        cur = cur->next;
    }
    return 0;
}


void matrixToList(Graph* graph, int** matrix, int n ) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
        int isDirected = 1;
            if(matrix[j][i] == 1) isDirected = 0; 
            if(matrix[i][j] == 1) {
                addEdge(graph, i, j, isDirected);
                printf(" %d - %d : %d |\n", i , j, isDirected);
            }
        }
    }
}