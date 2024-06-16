#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct node* nodePointer;
typedef struct node {
    int v, w, cost;
    nodePointer link;
} node;

nodePointer *graph;
nodePointer *rear;

nodePointer createNode(int v, int w, int cost) {
    nodePointer new;
    MALLOC(new, sizeof(node));
    new->v = v; new->w = w;
    new->cost = cost;
    new->link = NULL;

    return new;
}

void appendNode(int v, int w, int cost) {
    nodePointer new = createNode(v, w, cost);
    if (!rear[v]) graph[v] = new;
    else rear[v]->link = new;
    rear[v] = new;
}

void prim(int **result, int *tc, int size, FILE *f) {
    int *visited, i, j, isFirstEdge = 1;
    MALLOC(visited, sizeof(int) * size);
    nodePointer temp;

    for (i = 0; i < size; i++) visited[i] = 0;

    visited[0] = 1;
    
    while (1) {
        int minCost = INT_MAX, minV = -1, minW = -1;

        for (i = 0; i < size; i++)
            if (visited[i])
                for (temp = graph[i]; temp; temp = temp->link)
                    if (!visited[temp->w] && temp->cost < minCost) {
                        minCost = temp->cost;
                        minV = temp->v;
                        minW = temp->w;
                    }

        if (minCost == INT_MAX) break;

        visited[minW] = 1;

        if (isFirstEdge) {
            fprintf(f, "(%d, %d)", minV, minW);
            isFirstEdge = 0;
        } else {
            fprintf(f, ", (%d, %d)", minV, minW);
        }

        result[minV][minW] = minCost;
        result[minW][minV] = minCost;
        *tc += minCost;
    }

    free(visited);
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int size, i, j, data, **result, totalCost = 0;
    fscanf(f, "%d", &size);
    MALLOC(graph, sizeof(nodePointer) * size);
    MALLOC(rear, sizeof(nodePointer) * size);

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
    }
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(f, "%d ", &data);
            if (data) appendNode(i, j, data);
        }
    }

    fclose(f); 
    
    MALLOC(result, sizeof(int*) * size);
    for (i = 0; i < size; i++)
        MALLOC(result[i], sizeof(int) * size);

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            result[i][j] = 0;

    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    fprintf(f, "Adjacency matrix representation MCST = { ");

    prim(result, &totalCost, size, f);

    fprintf(f, " }\nTotal cost = %d\n\n", totalCost);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            fprintf(f, "%d ", result[i][j]);
        fprintf(f, "\n");
    } 

    fclose(f);
}