#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define END 100000

void initLoserTree(int* lt);
int* sort(int* lt, int* current_idx);

int** runs;
int row, col;
int i, j;

int main(int argc, char* argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) exit(1);

    int total;
    fscanf(f, "%d %d\n\n", &total, &row);
    col = total / row;

    runs = (int**)malloc(sizeof(int*) * row);
    for (i = 0; i < row; i++)
        runs[i] = (int*)malloc(sizeof(int) * col);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            fscanf(f, "%d ", &runs[i][j]);
        }
    }

    fclose(f);

    int* lt = (int*)malloc(sizeof(int) * (2 * row - 1));
    lt[0] = 0;
    int* current_idx = (int*)malloc(sizeof(int) * row);
    for (int i = 0; i < row; i++)
        current_idx[i] = 1;

    initLoserTree(lt);

    int* result = sort(lt, current_idx);

    f = fopen(argv[2], "w");
    if (f == NULL) exit(1);

    for (i = 0; i < row * col; i++)
        fprintf(f, "%d ", result[i]);
}


void initLoserTree(int* lt) {
    for (i = 0; i < row; i++)
        lt[row + i] = runs[i][0];

    for (i = row - 1; i > 0; i--) {
        if (lt[2 * i] < lt[2 * i + 1]) lt[i] = lt[2 * i];
        else lt[i] = lt[2 * i + 1];
    }
}


int* sort(int* tree, int* current_idx) {
    int* result = (int*)malloc(sizeof(int) * row * col);

    int min_idx;
    j = 0;
    while (tree[1] != 1000) {
        result[j++] = tree[1];

        for (int i = 0; i < row; i++) {
            if (tree[row + i] == tree[1]) {
                min_idx = i + row;

                if (current_idx[i] < col) tree[row + i] = runs[i][current_idx[i]++];
                else tree[row + i] = 1000;

                break;
            }
        }
        while (min_idx > 1) {
            min_idx /= 2;
            if (tree[2 * min_idx] < tree[2 * min_idx + 1]) tree[min_idx] = tree[2 * min_idx];
            else tree[min_idx] = tree[2 * min_idx + 1];
        }
    }

    return result;
}