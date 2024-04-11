#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
    int i, j, n, num = 0;

    FILE* infile, * outfile;
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    fscanf(infile, "%d", &n);
    for (i = 0; i < MAX_SIZE; i++)
    {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    for (int k = 0; k < n; k++) {
        fscanf(infile, "%d = %d", &i, &j);

        x = (nodePointer)malloc(sizeof(*x));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;

        x = (nodePointer)malloc(sizeof(*x));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
    }

    fprintf(outfile, "\n");
    int first = 1;
    for (i = 0; i < MAX_SIZE; i++) {
        if (out[i] && seq[i] != NULL) {
            if (!first)
                fprintf(outfile, ", ");
            else first = 0;
            fprintf(outfile, "{%d", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            num++;
            int elements[MAX_SIZE];
            int idx = 0;
            for (;;) {
                while (x) {
                    j = x->data;
                    if (out[j]) {
                        elements[idx++] = j;
                        out[j] = FALSE;
                        y = x->link;
                        x->link = top;
                        top = x;
                        x = y;
                    }
                    else x = x->link;
                }
                if (top == 0) break;
                x = seq[top->data];
                top = top->link;
            }
            sort(elements, idx);
            for (int m = 0; m < idx; m++) {
                fprintf(outfile, ", %d", elements[m]);
            }
            fprintf(outfile, "}");
        }
    }
    rewind(outfile);
    fprintf(outfile, "%d", num);

    fclose(infile);
    fclose(outfile);

    return 0;
}