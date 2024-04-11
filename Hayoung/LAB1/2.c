/* 아래와 같이 두 개의 정방행렬(n * n)을 곱해 그 결과를 출력하는 프로그램을 작성하시오. 단,
main 함수는 데이터를 입력하고 결과를 출력하는 역할을 담당하며 정방행렬을 곱하는 기능을 갖는
별도로 작성된 함수를 호출하여 처리한다. 정적 메모리 할당을 사용하며 n은 20 이하의 양의 정수이다. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 행렬 곱을 수행하는 함수
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

	for (i = 0; i < n; i++) // A 행렬 입력
	{
		for (j = 0; j < n; j++) {
			fscanf(infile, "%d", &A[i][j]);
		}
	}

	for (i = 0; i < n; i++) // B 행렬 입력
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
		fprintf(outfile, "\n"); // 1행 작성 후 다음 줄로
	}

	fclose(outfile);

	return 0;
}