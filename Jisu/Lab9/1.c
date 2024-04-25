#include <stdio.h>
#include <stdlib.h>

#define MAX 26

typedef struct node *nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

void createNode(int p, int q, nodePointer *seq) {
    nodePointer temp = seq[p];
    while (temp != NULL) {
        if (temp->data == q) {
            return;
        }
        temp = temp->link;
    }

    nodePointer newNodeP = (nodePointer)malloc(sizeof(node));
    nodePointer newNodeQ = (nodePointer)malloc(sizeof(node));
    if (!newNodeP || !newNodeQ) {
        printf("Insufficient memory");
        exit(1);
    }
    newNodeP->data = q;
    newNodeP->link = seq[p];
    seq[p] = newNodeP;

    newNodeQ->data = p;
    newNodeQ->link = seq[q];
    seq[q] = newNodeQ;
}

int countEquivalenceClasses(int n, nodePointer *seq) {
    int visited[MAX] = {0};
    int class_count = 0;

    for (int i = 0; i < n; i++) {
        if (seq[i] && !visited[i]) {
            class_count++;
            int stack[MAX];
            int top = -1;
            visited[i] = 1;
            stack[++top] = i;
            while (top != -1) {
                int current_index = stack[top--];
                nodePointer current = seq[current_index];
                while (current != NULL) {
                    if (!visited[current->data]) {
                        visited[current->data] = 1;
                        stack[++top] = current->data;
                    }
                    current = current->link;
                }
            }
        }
    }
    return class_count;
}

void printEquivalenceClasses(int n, nodePointer *seq, FILE *outf) {
    int visited[MAX] = {0};
    int stack[MAX];
    int top = -1;

    for (int i = 0; i < n; i++) {
        if (seq[i] && !visited[i]) {
            top = -1;
            if (i > 0) fprintf(outf, ", ");
            fprintf(outf, "{%d", i);
            visited[i] = 1;
            stack[++top] = i;
            while (top != -1) {
                int current_index = stack[top--];
                nodePointer current = seq[current_index];
                while (current != NULL) {
                    if (!visited[current->data]) {
                        fprintf(outf, ", %d", current->data);
                        visited[current->data] = 1;
                        stack[++top] = current->data;
                    }
                    current = current->link;
                }
            }
            fprintf(outf, "}");
        }
    }
}

int main(int ac, char* av[]) {
    nodePointer seq[MAX] = {NULL};
    int p, q, n, max_index = -1;
    FILE *inf, *outf;

    if (ac != 3) {
        printf("Usage: %s input_file output_file\n", av[0]);
        return 1;
    }

    if ((inf = fopen(av[1], "r")) == NULL) {
        printf("Error opening input file %s\n", av[1]);
        return 1;
    }

    if ((outf = fopen(av[2], "w")) == NULL) {
        printf("Error opening output file %s\n", av[2]);
        return 1;
    }

    fscanf(inf, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(inf, "%d = %d", &p, &q);
        if (p > max_index) max_index = p;
        if (q > max_index) max_index = q;
        createNode(p, q, seq);
    }

    int class_count = countEquivalenceClasses(max_index + 1, seq);

    fprintf(outf, "%d\n", class_count);
    printEquivalenceClasses(max_index + 1, seq, outf);

    fclose(inf);
    fclose(outf);

    return 0;
}
