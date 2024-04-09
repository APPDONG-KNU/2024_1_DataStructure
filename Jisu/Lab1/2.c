#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

void mul(int** a, int** b, int** c, int n) {
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			c[i][j] = 0;
			for (int k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void freeAry(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

void printAry(char* av, int** a, int n) {
    FILE *outf;
    if ((outf = fopen(av, "w")) == NULL) {
		printf("error1");
		exit(1);
	}
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(outf, "%-4d ", a[i][j]);
        fprintf(outf, "\n");
    }
    fclose(outf);
}

int main(int ac, char* av[]) {
    FILE *inf;
    int n, **a, **b, **c;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    fscanf(inf, "%d", &n);
    MALLOC(a, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(a[i], sizeof(int) * n);
    MALLOC(b, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(b[i], sizeof(int) * n);
    MALLOC(c, sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        MALLOC(c[i], sizeof(int) * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(inf, "%d", &a[i][j]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(inf, "%d", &b[i][j]);
    fclose(inf);
    printf("%d", n);
    printAry(av[2], a, n);
    printf("\n");
    printAry(av[2], a, n);

    mul(a, b, c, n);

    printAry(av[2], c, n);

    freeAry(a, n);
    freeAry(b, n);
    freeAry(c, n);
    return 0;
}
