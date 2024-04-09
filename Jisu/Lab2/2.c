#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

int main(int ac, char* av[]) {
	FILE* inf, * outf;
	int n;
    double *a;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d", &n);
	MALLOC(a, sizeof(double) * n);
	for (int i = 0; i < n; i++)
		fscanf(inf, "%lf ", a + i);
	fclose(inf);
    
    double max = a[0], min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max) max = a[i];
        else if (a[i] < min) min = a[i];
    }

	if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error1");
		return 1;
	}
	fprintf(outf, "%.1lf %.1lf", max, min);
	fclose(outf);
    free(a);

	return 0;
}
