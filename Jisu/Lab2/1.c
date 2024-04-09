#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

void sumAry(int** a, int** b, int** c, int n, int m) {
    for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			c[i][j] = a[i][j] + b[i][j];
}

void freeAry(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

void printAry(char* av, int** a, int n, int m) {
    FILE *outf;
    if ((outf = fopen(av, "w")) == NULL) {
		printf("error1");
		exit(1);
	}
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            fprintf(outf, "%-4d ", a[i][j]);
        fprintf(outf, "\n");
    }
    fclose(outf);
}

int main(int ac, char* av[]) {
    FILE *inf;
    int n, m, **a, **b, **c;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    fscanf(inf, "%d %d", &n, &m);
    MALLOC(a, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(a[i], sizeof(int) * m);
    MALLOC(b, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(b[i], sizeof(int) * m);
    MALLOC(c, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(c[i], sizeof(int) * m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(inf, "%d", &a[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fscanf(inf, "%d", &b[i][j]);
    fclose(inf);
    printAry(av[2], a, n, m);
    printf("\n");
    printAry(av[2], a, n, m);

    sumAry(a, b, c, n, m);

    printAry(av[2], c, n, m);

    freeAry(a, n);
    freeAry(b, n);
    freeAry(c, n);
    return 0;
}
