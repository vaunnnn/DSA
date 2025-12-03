#include <stdio.h>
#include <stdlib.h>

int** initializeMatrix(int n);
void addEdge(int **matrix, int u, int v, int isDirected);
void removeEdge(int **matrix, int u, int v, int isDirected);
int hasEdge(int **matrix, int u, int v);
void printMatrix(int **matrix, int n);
void getNeighbors(int **matrix, int n, int u);
void freeMatrix(int **matrix, int n);



int main() {
    int n = 4; // number of nodes
    int **matrix = initializeMatrix(n);

    addEdge(matrix, 0, 1, 1);  // undirected
    addEdge(matrix, 0, 3, 1);
    addEdge(matrix, 1, 2, 1);
    addEdge(matrix, 3, 1, 1);
    addEdge(matrix, 3, 2, 1);

    printMatrix(matrix, n);


    getNeighbors(matrix, n, 3);

    freeMatrix(matrix, n);
    return 0;

}

int** initializeMatrix(int n) {
    int** matrix = (int**)malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
    }
    return matrix;
}

void addEdge(int **matrix, int u, int v, int isDirected) {
    matrix[u][v] = 1;
    if(!isDirected) {
        matrix[v][u] = 1;
    }
}

void removeEdge(int **matrix, int u, int v, int isDirected) {
    matrix[u][v] = 0;
    if(!isDirected) {
        matrix[v][u] = 0;
    }
}

int hasEdge(int **matrix, int u, int v) {
    return matrix[u][v] == 1;
}

void printMatrix(int **matrix, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void getNeighbors(int **matrix, int n, int u) {
    for(int i = 0; i < n; i++) {
        if(matrix[u][i] == 1) { 
            printf("%d ", i);    
        }
    }
    printf("\n");
}

void freeMatrix(int **matrix, int n) {
    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }

    free(matrix);
}