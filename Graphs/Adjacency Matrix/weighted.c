#include <stdio.h>
#include <stdlib.h>
#define INF 999

int** initializeWeightedMatrix(int n);
void addWeightedEdge(int **matrix, int u, int v, int weight, int isDirected);
void removeWeightedEdge(int **matrix, int u, int v, int isDirected);
int getWeight(int **matrix, int u, int v);
void printWeightedMatrix(int **matrix, int n);
void getWeightedNeighbors(int **matrix, int n, int u);
void freeWeightedMatrix(int **matrix, int n);


int main() {
    int n = 4;
    int **matrix = initializeWeightedMatrix(n);

    // Add a few edges
    addWeightedEdge(matrix, 0, 1, 5, 1);
    addWeightedEdge(matrix, 1, 2, 7, 1);
    addWeightedEdge(matrix, 3, 1, 5, 1); 
    addWeightedEdge(matrix, 3, 2, 9, 1); 

    printf("Weighted adjacency matrix:\n");
    printWeightedMatrix(matrix, n);

    printf("\nNeighbors of node 0: ");
    getWeightedNeighbors(matrix, n, 0);

    printf("\nWeight from 0 to 2: %d\n", getWeight(matrix, 0, 2));

    // Remove an edge
    removeWeightedEdge(matrix, 0, 1, 0);

    printf("\nAfter removing edge 0-1:\n");
    printWeightedMatrix(matrix, n);

    freeWeightedMatrix(matrix, n);
    return 0;

}

int** initializeWeightedMatrix(int n) {
    int** matrix = (int**)malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++) {
            matrix[i][j] = INF;
        }
    }

    return matrix;
}

void addWeightedEdge(int **matrix, int u, int v, int weight, int isDirected) {
    matrix[u][v] = weight;
    if(!isDirected) {
        matrix[v][u] = weight;
    }
}

void removeWeightedEdge(int **matrix, int u, int v, int isDirected) {
    matrix[u][v] = INF;
    if(!isDirected) {
        matrix[u][v] = INF;
    }
}

int getWeight(int **matrix, int u, int v) {
    return matrix[u][v];
}

void printWeightedMatrix(int **matrix, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%-5d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void getWeightedNeighbors(int **matrix, int n, int u) {
    for(int i = 0; i < n; i++) {
        if(matrix[u][i] != INF) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void freeWeightedMatrix(int **matrix, int n) {
    for(int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}