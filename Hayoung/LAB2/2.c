#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	FILE* infile, * outfile;
	int n;

	infile = fopen(argv[1], "r");
	fscanf(infile, "%d", &n);

	double* num = (double*)malloc(n * sizeof(double));

	for (int i = 0; i < n; i++)
		fscanf(infile, "%lf", &num[i]);

	fclose(infile);

	outfile = fopen(argv[2], "w");
	for (int i = 0; i < n; i++) {
		double decimal = num[i] - (int)num[i];
		if (decimal != 0) {
			fprintf(outfile, "%.1f", num[i]);
			fprintf(outfile, " ");
		}
	}
	fclose(outfile);

	return 0;
}