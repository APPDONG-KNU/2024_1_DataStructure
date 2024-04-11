/* �Ʒ��� ���� �� ���� �������(n * n)�� ���� �� ����� ����ϴ� ���α׷��� �ۼ��Ͻÿ�. ��,
main �Լ��� �����͸� �Է��ϰ� ����� ����ϴ� ������ ����ϸ� ��������� ���ϴ� ����� ����
������ �ۼ��� �Լ��� ȣ���Ͽ� ó���Ѵ�. ���� �޸� �Ҵ��� ����ϸ� n�� 20 ������ ���� �����̴�. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ��� ���� �����ϴ� �Լ�
void mul(int n, int A[][20], int B[][20], int C[][20]) {
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			C[i][j] = 0;
			for (k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

int main(int argc, char* argv[]) {
	FILE* infile, * outfile;
	int n, A[20][20], B[20][20], C[20][20];
	int i, j;

	infile = fopen(argv[1], "r");
	if (infile == NULL)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	fscanf(infile, "%d", &n);

	for (i = 0; i < n; i++) // A ��� �Է�
	{
		for (j = 0; j < n; j++) {
			fscanf(infile, "%d", &A[i][j]);
		}
	}

	for (i = 0; i < n; i++) // B ��� �Է�
	{
		for (j = 0; j < n; j++) {
			fscanf(infile, "%d", &B[i][j]);
		}
	}

	fclose(infile);

	mul(n, A, B, C);

	outfile = fopen(argv[2], "w");
	if (outfile == NULL) {
		fprintf(stderr, "Error");
		return 1;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(outfile, "%d", C[i][j]);
			if (j < n - 1) {
				fprintf(outfile, " ");
			}
		}
		fprintf(outfile, "\n"); // 1�� �ۼ� �� ���� �ٷ�
	}

	fclose(outfile);

	return 0;
}