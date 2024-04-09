#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

int iterative(int* a, int n, int m) {
    int left = 0, right = n - 1, b, mid;
	
	while (1) {
		if (left <= right) {
		    mid = (left + right) / 2;
		    switch (COMPARE(a[mid], m)) {
		    case -1: left = mid + 1; break;
		    case 0: b = -1; break;
		    case 1: right = mid - 1;;
		}
		}
		if (b == -1) break;
	}
    return mid;
}

int main(int ac, char* av[]) {
	FILE* inf, * outf;
	int n, m, mid, *a;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d %d", &n, &m);
	MALLOC(a, sizeof(int) * n);
	for (int i = 0; i < n; i++)
		fscanf(inf, "%d ", a + i);
	fclose(inf);

	mid = iterative(a, n, m);

	if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error1");
		return 1;
	}
	fprintf(outf, "%d", mid);
	fclose(outf);
    free(a);

	return 0;
}
