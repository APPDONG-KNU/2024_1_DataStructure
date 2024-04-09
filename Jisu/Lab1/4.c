#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

int binsearch(int* a, int sn, int left, int right) {
	int mid;
	if (left <= right) {
		mid = (left + right) / 2;
		switch (COMPARE(a[mid], sn)) {
		case -1: return binsearch(a, sn, mid + 1, right);
		case 0: return mid;
		case 1: return binsearch(a, sn, left, mid - 1);
		}
		return -1;
	}
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

	mid = binsearch(a, m, 0, n - 1);

	if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error1");
		return 1;
	}
	fprintf(outf, "%d", mid);
	fclose(outf);
    free(a);

	return 0;
}
