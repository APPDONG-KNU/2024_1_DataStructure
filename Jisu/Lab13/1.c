#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

void makeBT(FILE* f, int** a, int* i) {
    int n;
    while (fscanf(f, "%d", &n) != EOF) {
        (*i)++;
        if (n == -1)
            *a = (int*)realloc(*a, sizeof(int) * ((*i) + 1));
        (*a)[(*i) - 1] = n;
    }
}

int main(int ac, char* av[]) {
    FILE *f1, *f2;
    int *a1, *a2;
    int n1, n2, f = 1, i1 = 0, i2 = 0;
    
    if (ac < 3) {
        printf("Usage: %s file1 file2\n", av[0]);
        return 1;
    }

    f1 = fopen(av[1], "r");
    f2 = fopen(av[2], "r");
    if (f1 == NULL || f2 == NULL) {
        printf("Failed to open files\n");
        return 1;
    }
    
    fscanf(f1, "%d", &n1);
    fscanf(f2, "%d", &n2);
    MALLOC(a1, sizeof(int) * n1);
    MALLOC(a2, sizeof(int) * n2);
    
    makeBT(f1, &a1, &i1);
    makeBT(f2, &a2, &i2);
    if (n1 != n2)
        f = 0;
    else {
        for (int j = 0; j < i1; j++)
            if (a1[j] != a2[j]) {
                f = 0;
                break;
            }
    }
    
    if (f)
        printf("Same\n");
    else
        printf("Different\n");

    free(a1);
    free(a2);
    fclose(f1);
    fclose(f2);
    
    return 0;
}
