#define _CRT_SECURE_NO_WARNINGS
#define MAX_DEGREE 20
#include <stdio.h>

void addPoly(int a[][2], int n, int m, int d[][2], int* c) {
	int i = 0, j = n, k = 0;

	while (i < n || j < n + m) {
		if (i < n && (j >= n + m || a[i][1] > a[j][1])) {
			d[k][0] = a[i][0];
			d[k][1] = a[i][1];
			i++;
			k++;
		}
		else if (j < n + m && (i >= n || a[i][1] < a[j][1])) {
			d[k][0] = a[j][0];
			d[k][1] = a[j][1];
			j++;
			k++;
		}
		else {
			d[k][0] = a[i][0] + a[j][0];
			d[k][1] = a[i][1];
			i++;
			j++;
			k++;
		}
		*c = k;
	}
}


int main(int argc, char* argv[]) {
	int a[MAX_DEGREE][2], d[MAX_DEGREE][2];
	int n, m, c;

	FILE* infile, * outfile;
	infile = fopen(argv[1], "r");
	fscanf(infile, "%d %d\n", &n, &m);

	for (int i = 0; i < n + m; i++)
	{
		fscanf(infile, "%d %d", &a[i][0], &a[i][1]);

	}

	addPoly(a, n, m, d, &c);

	outfile = fopen(argv[2], "w");
	for (int i = 0; i < c; i++)
	{
		fprintf(outfile, "%d %d\n", d[i][0], d[i][1]);
	}

	fclose(infile);
	fclose(outfile);

	return 0;
}