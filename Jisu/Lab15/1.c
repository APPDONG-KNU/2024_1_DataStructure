#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

int **runs;
int row, col;
int i, j;

void LoserTree(int *lt) {
    for (i = 0; i < row; i++)
        lt[row + i] = runs[i][0];
    
    for (i = row - 1; i > 0; i--) {
        if (lt[2 * i] < lt[2 * i + 1]) lt[i] = lt[2 * i];
        else lt[i] = lt[2 * i + 1];
    }
}

int* sort(int *tree, int *ci) {
   int *result;
   MALLOC(result, sizeof(int) * row * col);

    int min_idx;
    j = 0;
    while(tree[1] != 100000) {
        result[j++] = tree[1];

        for(i = 0; i < row; i++){
            if(tree[row + i] == tree[1]){
                min_idx = i + row;

                if(ci[i] < col) tree[row + i] = runs[i][ci[i]++];
                else tree[row + i] = 100000;

                break;
            }
        }
        while(min_idx > 1){
            min_idx /= 2;
            if(tree[2 * min_idx] < tree[2 * min_idx + 1]) tree[min_idx] = tree[2 * min_idx];
            else tree[min_idx] = tree[2 * min_idx + 1];
        }
    }

    return result;
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int total, *lt, *ci;
    fscanf(f, "%d %d\n\n", &total, &row);
    col = total / row;

    MALLOC(runs, sizeof(int*) * row);
    for (i = 0; i < row; i++)
        MALLOC(runs[i], sizeof(int) * col);
   
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            fscanf(f, "%d ", &runs[i][j]);

    fclose(f);

    MALLOC(lt, sizeof(int) * (2 * row - 1));
    lt[0] = 0;
    MALLOC(ci, sizeof(int) * row);
    for (i = 0; i < row; i++)
        ci[i] = 1;
    
    LoserTree(lt);

    int *result = sort(lt, ci);
    
    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    for (i = 0; i < row * col; i++)
        fprintf(f, "%d ", result[i]);
}