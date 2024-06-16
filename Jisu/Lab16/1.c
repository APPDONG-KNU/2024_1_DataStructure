#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
}node;

nodePointer *graph, *rear;
int *visited;

nodePointer createNode(int item) {
    nodePointer new;
    MALLOC(new, sizeof(node));
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

void dfsst(int **result, int v ,FILE *f) {
    visited[v] = 1;

    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            if (v == 0) fprintf(f, " (%d, %d)", v, w->vertex);
            else fprintf(f, ", (%d, %d)", v, w->vertex);
            result[v][w->vertex] = 1;
            result[w->vertex][v] = 1;
            dfsst(result, w->vertex, f);
        }
    }
}

void dfs(int v, FILE *f) {
    visited[v] = 1;
    fprintf(f, "%d, ", v);

    for (nodePointer w = graph[v]; w; w = w->link) {
        if (!visited[w->vertex]) {
            dfs(w->vertex, f);
        }
    }
}

void connected(int size, FILE *f) {
    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            fprintf(f, "{");
            dfs(i, f);
            fprintf(f, "}, ");
        }
    }
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int size, i, j, d, cnt = 0, **result;

    fscanf(f, "%d\n", &size);
    MALLOC(graph, sizeof(nodePointer) * size);
    MALLOC(rear ,sizeof(nodePointer) * size);
    MALLOC(visited, sizeof(int) * size);

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
        visited[i] = 0;
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fscanf(f, "%d ", &d);
            if (d) {
                appendNode(i, j);
                cnt++;
            }
        }
    }
    fclose(f);

    MALLOC(result, sizeof(int*) * cnt);
    for (i = 0; i < cnt; i++)
        MALLOC(result[i], sizeof(int) * cnt);

    for (i = 0; i < cnt; i++)
        for (j = 0; j < cnt; j++)
            result[i][j] = 0;

    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    fprintf(f, "adjacency matrix (%d by %d), Tree Edges = { ", size, size);

    dfsst(result, 0, f);
    fprintf(f, " }\n");

    int stExists = 1;
    for (i = 0; i < size; i++)
        if (!visited[i]) {
            stExists = 0;
            break;
        }

    for (i = 0; i < size; i++) 
        visited[i] = 0;

    if (stExists)
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++)
                fprintf(f, "%d ", result[i][j]);
            fprintf(f, "\n");
        }   
    else connected(size, f);

    fclose(f);
}