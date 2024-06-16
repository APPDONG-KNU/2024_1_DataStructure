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

nodePointer *graph, *rear, front = NULL, rearQ = NULL;
int *visited;

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

void bfsst(int ** result, int v, FILE *f) {
    front = rearQ = NULL; 

    visited[v] = 1;
    addq(v);

    while (front) {
        v = deleteq();

        for (nodePointer w = graph[v]; w; w = w->link)
            if (!visited[w->vertex]) {
                if (w == graph[0]) fprintf(f, " (%d, %d)", v, w->vertex);
                else fprintf(f, ", (%d, %d)", v, w->vertex);
                result[v][w->vertex] = 1;
                result[w->vertex][v] = 1;
                addq(w->vertex);
                visited[w->vertex] = 1;
            }
    }
}

void dfs(int v, FILE *f) {
    visited[v] = 1;
    fprintf(f, "%d, ", v);

    for (nodePointer w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex, f);
}

void connected(int size, FILE *f) {
    for (int i = 0; i < size; i++)
        if (!visited[i]) {
            fprintf(f, "{");
            dfs(i, f);
            fprintf(f, "}, ");
        }
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int size, i, j, **result;
    fscanf(f, "%d\n", &size);
    MALLOC(graph, sizeof(nodePointer) * size);
    MALLOC(rear, sizeof(nodePointer) * size);
    MALLOC(visited, sizeof(int) * size);

    for (i = 0; i < size; i++) {
        graph[i] = NULL;
        rear[i] = NULL;
        visited[i] = 0;
    }

    int data, cnt = 0;    
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++) {
            fscanf(f, "%d ", &data);
            if (data) {
                appendNode(i, j);
                cnt++;
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

    bfsst(result, 0, f);
    fprintf(f, " }\n");

    int stExists = 1;
    for (i = 0; i < size; i++)
        if (!visited[i]) {
            stExists = 0;
            break;
        }

    for (i = 0; i < size; i++) 
        visited[i] = 0;

    if (stExists) {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++)
                fprintf(f, "%d ", result[i][j]);
            fprintf(f, "\n");
        }   
    } else connected(size, f);

    fclose(f);
}