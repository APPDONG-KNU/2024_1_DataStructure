#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }

typedef struct node* nodePointer;
typedef struct node {
    int v, w;
    int cost;
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
    if (v > w) {
        int temp = v;
        v = w;
        w = temp;
    }
    nodePointer new = createNode(v, w, cost);
    if (!rear[v]) graph[v] = new;
    else rear[v]->link = new;
    rear[v] = new;
}

void makeSet(int *parent, int size) {
    for (int i = 0; i < size; i++)
        parent[i] = i;
}

int findSet(int *parent, int i) {
    if (parent[i] == i)
        return i;
    return findSet(parent, parent[i]);
}

void unionSets(int *parent, int i, int j) {
    int set_i = findSet(parent, i);
    int set_j = findSet(parent, j);
    parent[set_i] = set_j;
}

int inSameSet(int *parent, int i, int j) {
    return findSet(parent, i) == findSet(parent, j);
}

void kruskal(int **result, int *tc, int size, FILE *f) {
    int *parent;
    MALLOC(parent, sizeof(int) * size);
    makeSet(parent, size);

    nodePointer temp, min, minPrev, prev;
    int addedNode = 0, isFirstEdge = 1;

    while (addedNode < size - 1) {
        min = NULL;
        minPrev = NULL;

        for (int i = 0; i < size; i++) {
            prev = NULL;
            for (temp = graph[i]; temp; prev = temp, temp = temp->link) {
                if (!min || temp->cost < min->cost) {
                    min = temp;
                    minPrev = prev;
                }
            }
        }

        if (min == NULL) break;

        if (minPrev == NULL) {
            graph[min->v] = min->link;
            if (rear[min->v] == min)
                rear[min->v] = NULL;
        } else {
            minPrev->link = min->link;
            if (rear[min->v] == min)
                rear[min->v] = minPrev;
        }

        if (!inSameSet(parent, min->v, min->w)) {
            addedNode++;
            result[min->v][min->w] = min->cost;
            result[min->w][min->v] = min->cost;

            if (isFirstEdge) {
                fprintf(f, "(%d, %d)", min->v, min->w);
                isFirstEdge = 0;
            } else {
                fprintf(f, ", (%d, %d)", min->v, min->w);
            }

            *tc += min->cost;
            unionSets(parent, min->v, min->w);
        }
        free(min);
    }
    free(parent);
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int size, data, **result, totalCost = 0;
    fscanf(f, "%d", &size);
    MALLOC(graph, sizeof(nodePointer) * size);
    MALLOC(rear, sizeof(nodePointer) * size);
    int i, j;

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
    }

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++) {
            fscanf(f, "%d ", &data);
            if (data) appendNode(i, j, data); 
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

    kruskal(result, &totalCost, size, f);

    fprintf(f, " }\nTotal cost = %d\n\n", totalCost);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++)
            fprintf(f, "%d ", result[i][j]);
        fprintf(f, "\n");
    } 

    fclose(f);
}