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

Graph *createGraph(int vertices);
Node *createNode(int vertex);

void addEdge(Graph *graph, int src, int dest, int isDirected);
void removeEdge(Graph *graph, int src, int dest, int isDirected);

void printGraph(Graph *graph);
void getNeighbors(Graph *graph, int vertex);

int hasEdge(Graph *graph, int src, int dest);
int degree(Graph *graph, int vertex);

void freeGraph(Graph *graph);

int main()
{

    Graph *graph = createGraph(4);

    // Add some edges
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 0, 3, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 3, 1, 1);
    addEdge(graph, 3, 2, 1);

    printf("Graph adjacency list:\n");
    printGraph(graph);

    printf("\nNeighbors of vertex 1: ");
    getNeighbors(graph, 1);

    printf("\nDegree of vertex 1: %d\n", degree(graph, 1));

    printf("Does edge 0-4 exist? %s\n", hasEdge(graph, 0, 4) ? "Yes" : "No");
    printf("Does edge 2-4 exist? %s\n", hasEdge(graph, 2, 4) ? "Yes" : "No");

    // Remove an edge
    printf("\nRemoving edge 1-4...\n");
    removeEdge(graph, 1, 4, 0);

    printGraph(graph);

    freeGraph(graph);
    return 0;
}

Graph *createGraph(int vertices)
{
    Graph *list = (Graph *)malloc(sizeof(Graph));

    list->numVertices = vertices;
    list->adjList = (Node **)malloc(sizeof(Node *) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        list->adjList[i] = NULL;
    }
    return list;
}

Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph *graph, int src, int dest, int isDirected)
{
    Node *newNode = createNode(dest);

    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!isDirected)
    {
        Node *newNode2 = createNode(src);
        newNode2->next = graph->adjList[dest];
        graph->adjList[dest] = newNode2;
    }
}

void removeEdge(Graph *graph, int src, int dest, int isDirected)
{
    Node *curr = graph->adjList[src];
    Node *prev = NULL;
    while (curr != NULL && curr->vertex != dest)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    if (prev == NULL)
    {
        graph->adjList[src] = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }
    free(curr);

    if (!isDirected)
    {
        curr = graph->adjList[dest];
        prev = NULL;
        while (curr != NULL && curr->vertex != src)
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL)
            return;

        if (prev == NULL)
        {
            graph->adjList[src] = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        free(curr);
    }
}

void printGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d: ", i);
        Node *temp = graph->adjList[i];
        while (temp != NULL)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void getNeighbors(Graph *graph, int vertex)
{
    Node *temp = graph->adjList[vertex];
    for (int i = 0; temp != NULL; i++)
    {
        printf("%d ", temp->vertex);
        temp = temp->next;
    }
    printf("\n");
}

int hasEdge(Graph *graph, int src, int dest)
{
    Node *curr = graph->adjList[src];
    while (curr != NULL)
    {
        if (curr->vertex == dest)
            return 1;
        curr = curr->next;
    }
    return 0;
}

int degree(Graph *graph, int vertex)
{
    int count = 0;
    Node *curr = graph->adjList[vertex];
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *curr = graph->adjList[i];
        while (curr != NULL)
        {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(graph->adjList);
    free(graph);
}