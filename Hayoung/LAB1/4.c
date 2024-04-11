// 3.c 문제를 recursive 방식으로 수행하시오

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int bs(int arr[], int left, int right, int m) {
	if (left <= right)
	{
		int t = left + (right - left) / 2;

		if (arr[t] == m)
			return t;
		else if (arr[t] < m)
			return bs(arr, t + 1, right, m); // recursive
		else
			return bs(arr, left, t - 1, m);
	}

	return -1;
}

int main(int argc, char* argv[]) {
	FILE* infile, * outfile;
	int n, m, i;
	int arr[10];

	infile = fopen(argv[1], "r");
	if (infile == NULL)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	fscanf(infile, "%d %d", &n, &m);
	if (n <= 0 || n > 10)
	{
		fprintf(stderr, "Error");
		fclose(infile);
		return 1;
	}

	for (i = 0; i < n; i++)
	{
		fscanf(infile, "%d", &arr[i]);
	}

	fclose(infile);

	int index = bs(arr, 0, n-1, m);

	outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		fprintf(stderr, "Error");
		return 1;
	}

	fprintf(outfile, "%d\n", index);

	fclose(outfile);

	return 0;
}