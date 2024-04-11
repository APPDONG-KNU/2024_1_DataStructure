#define _CRT_SECURE_NO_WARNINGS
#define MAX_DEGREE 20
#include <stdio.h>

struct item {
	int coef;
	int exp;
};

void addPoly(struct item a[], int n, int m, struct item d[], int* c) {
	int i = 0, j = n, k = 0;

	while (i < n || j < n+m) {
		if (i < n && (j >= n+m || a[i].exp > a[j].exp)) {
			d[k] = a[i];
			k++;
			i++;
		}
		else if (j < n+m && (i >= n || a[i].exp < a[j].exp)) {
			d[k] = a[j];
			k++;
			j++;
		}
		else {
			d[k].coef = a[i].coef + a[j].coef;
			d[k].exp = a[i].exp;
			k++;
			i++;
			j++;
		}
	}


	*c = k;
}

int main(int argc, char* argv[]) {
	struct item a[MAX_DEGREE], d[MAX_DEGREE];
	int n, m, c;

	FILE* infile, * outfile;
	infile = fopen(argv[1], "r");
	fscanf(infile, "%d %d", &n, &m);

	for (int i = 0; i < n+m; i++)
	{
		fscanf(infile, "\n %d %d", &a[i].coef, &a[i].exp);
	}

	addPoly(a, n, m, d, &c);

	outfile = fopen(argv[2], "w");
	for (int i = 0; i < c; i++)
	{
		fprintf(outfile, "%d %d\n", d[i].coef, d[i].exp);
	}

	fclose(infile);
	fclose(outfile);

	return 0;
}