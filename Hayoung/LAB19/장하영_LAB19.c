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
void prim(int** result, int* tc, int size, FILE* f);

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
    prim(result, &totalCost, size, outfile);

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



void prim(int** result, int* tc, int size, FILE* f) {
    int* visited = (int*)malloc(sizeof(int) * size);
    int i, j;
    nodePointer temp;

    for (i = 0; i < size; i++) {
        visited[i] = FALSE;
    }

    visited[0] = TRUE;

    while (TRUE) {
        int minCost = 1000000;
        int minV, minW;

        for (i = 0; i < size; i++) {
            if (visited[i]) {
                for (temp = graph[i]; temp; temp = temp->link) {
                    if (!visited[temp->w] && temp->cost < minCost) {
                        minCost = temp->cost;
                        minV = temp->v;
                        minW = temp->w;
                    }
                }
            }
        }

        if (minCost == 1000000) {
            break;
        }

        visited[minW] = TRUE;

        fprintf(f, "(%d, %d) ", minV, minW);
        result[minV][minW] = minCost;
        result[minW][minV] = minCost;
        *tc += minCost;
    }
}
