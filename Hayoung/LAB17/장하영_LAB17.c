#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct node* nodePointer;
typedef struct node {
    int v, w;
    int cost;
    nodePointer link;
}node;


nodePointer createNode(int v, int w, int cost);
void appendNode(int v, int w, int cost);
void makeSet(int* parent, int size);
int findSet(int* parent, int i);
void unionSets(int* parent, int i, int j);
int inSameSet(int* parent, int i, int j);
void kruskal(int** result, int* tc, int size, FILE* f);

nodePointer* graph;
nodePointer* rear;


int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    infile = fopen(argv[1], "r");
    if (infile == NULL) exit(1);

    int size;
    fscanf(infile, "%d\n", &size);
    graph = (nodePointer*)malloc(sizeof(nodePointer) * size);
    rear = (nodePointer*)malloc(sizeof(nodePointer) * size);
    int i, j;

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
    }


    int data, cntForcost = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(infile, "%d ", &data);
            if (data) {
                appendNode(i, j, data);
            }
        }
    }

    fclose(infile);

    int** result = (int**)malloc(sizeof(int*) * size);
    for (i = 0; i < size; i++)
        result[i] = (int*)malloc(sizeof(int) * size);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            result[i][j] = 0;
        }
    }

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) exit(1);


    fprintf(outfile, "Adjacency matrix representation MCST = { ");

    int totalCost = 0;
    kruskal(result, &totalCost, size, infile);

    fprintf(outfile, "}\nTotal cost = %d\n\n", totalCost);

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fprintf(outfile, "%d ", result[i][j]);
        }
        fprintf(outfile, "\n");
    }


    fclose(outfile);
}


nodePointer createNode(int v, int w, int cost) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
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


void makeSet(int* parent, int size) {
    for (int i = 0; i < size; i++) {
        parent[i] = i;
    }
}

int findSet(int* parent, int i) {
    if (parent[i] == i)
        return i;
    return findSet(parent, parent[i]);
}

void unionSets(int* parent, int i, int j) {
    int set_i = findSet(parent, i);
    int set_j = findSet(parent, j);
    parent[set_i] = set_j;
}

int inSameSet(int* parent, int i, int j) {
    return findSet(parent, i) == findSet(parent, j);
}

void kruskal(int** result, int* tc, int size, FILE* f) {
    int* parent = (int*)malloc(sizeof(int) * size);
    makeSet(parent, size);

    int addedNode = 0;
    nodePointer temp, min;
    int i, j;

    while (addedNode < size - 1) {
        min = createNode(1000, 1000, 100000);

        for (i = 0; i < size; i++) {
            for (temp = graph[i]; temp; temp = temp->link) {
                if (min->cost > temp->cost) min = temp;
            }
        }

        if (min == graph[min->v]) {
            graph[min->v] = min->link;
            if (rear[min->v] == min)
                rear[min->v] = NULL;
        }
        else {
            for (temp = graph[min->v]; temp->link != min; temp = temp->link);
            temp->link = min->link;
            if (rear[min->v] == min)
                rear[min->v] = temp;
        }

        int hasCycle = inSameSet(parent, min->v, min->w);

        if (!hasCycle) {
            addedNode++;
            result[min->v][min->w] = min->cost;
            result[min->w][min->v] = min->cost;
            fprintf(f, "(%d, %d) ", min->v, min->w);
            *tc += min->cost;
            unionSets(parent, min->v, min->w);
        }

        free(min);
    }

    free(parent);
}



