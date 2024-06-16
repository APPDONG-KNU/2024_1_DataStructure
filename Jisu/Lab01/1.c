#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

int arraySum(int* a, int n) {
    int s = 0;
    for (int i = 0; i < n; i++)
        s += *(a + i);
    return s;
}

int main(int ac, char* av[]) {
    FILE *inf, *outf;
    int n, *a;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    fscanf(inf, "%d", &n);
    MALLOC(a, sizeof(int) * n);
    for (int i = 0; i < n; i++)
        fscanf(inf, "%d", a + i);
    fclose(inf);
    
    int sum = arraySum(a, n);
    
    if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error1");
		return 1;
	}
    fprintf(outf, "%d", sum);
    fclose(outf);
    free(a);

    return 0;
}
