#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
}node;


nodePointer createNode(int item);
void appendNode(int v, int w);
void addq(int item);
int deleteq();
void bfsSpanningTree(int** result, int v, FILE* f);
void dfs(int v, FILE* f);
void connected(int size, FILE* f);


nodePointer* graph;
nodePointer* rear;
int* visited;

nodePointer front = NULL, rearQ = NULL;


int main(int argc, char* argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) exit(1);

    int size;
    fscanf(f, "%d\n", &size);
    graph = (nodePointer*)malloc(sizeof(nodePointer) * size);
    rear = (nodePointer*)malloc(sizeof(nodePointer) * size);
    visited = (int*)malloc(sizeof(int) * size);

    int i, j;

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
        visited[i] = FALSE;
    }

    int data, cnt = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                appendNode(i, j);
                cnt++;
            }
        }
    }

    fclose(f);

    int** result = (int**)malloc(sizeof(int*) * cnt);
    for (i = 0; i < cnt; i++)
        result[i] = (int*)malloc(sizeof(int) * cnt);

    for (i = 0; i < cnt; i++) {
        for (j = 0; j < cnt; j++) {
            result[i][j] = 0;
        }
    }

    f = fopen(argv[2], "w");
    if (f == NULL) exit(1);

    fprintf(f, "adjacency matrix (%d by %d), Tree Edges = { ", size, size);

    bfsSpanningTree(result, 0, f);
    fprintf(f, "}\n");

    int spanningTreeExists = TRUE;
    for (i = 0; i < size; i++) {
        if (!visited[i]) {
            spanningTreeExists = FALSE;
            break;
        }
    }

    for (i = 0; i < size; i++)
        visited[i] = FALSE;

    if (spanningTreeExists) {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fprintf(f, "%d ", result[i][j]);
            }
            fprintf(f, "\n");
        }
    }
    else connected(size, f);

    fclose(f);
}


nodePointer createNode(int item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->vertex = item;
    new->link = NULL;

    return new;
}


void appendNode(int v, int w) {
    nodePointer new = createNode(w);
    if (!rear[v]) graph[v] = new;
    else rear[v]->link = new;
    rear[v] = new;
}


void addq(int item) {
    nodePointer new = createNode(item);
    if (!front) front = new;
    else rearQ->link = new;
    rearQ = new;
}

int deleteq() {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }

    int item = front->vertex;

    if (front == rearQ) front = rearQ = NULL;
    else front = front->link;

    return item;
}

void bfsSpanningTree(int** result, int v, FILE* f) {
    front = rearQ = NULL;

    visited[v] = TRUE;
    addq(v);

    while (front) {
        v = deleteq();

        for (nodePointer w = graph[v]; w; w = w->link) {
            if (!visited[w->vertex]) {
                fprintf(f, "(%d, %d), ", v, w->vertex);
                result[v][w->vertex] = 1;
                result[w->vertex][v] = 1;
                addq(w->vertex);
                visited[w->vertex] = TRUE;
            }
        }
    }
}


void dfs(int v, FILE* f) {
    visited[v] = TRUE;
    fprintf(f, "%d, ", v);

    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex, f);
        }
    }
}


void connected(int size, FILE* f) {
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            fprintf(f, "{");
            dfs(i, f);
            fprintf(f, "}, ");
        }
    }
}


