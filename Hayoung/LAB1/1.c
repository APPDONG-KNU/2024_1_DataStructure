/* 다음과 같이 0이 아닌 양의 정수 n의 크기를 지니는 일차원 정수 배열을 동적 메모리 할
당을 이용하여 구현한 후, 다음과 같은 양식의 input.txt 파일에서 n개의 정수를 읽어 배열에 
저장하시오. 그리고 배열에 저장된 정수들을 모두 더한 결과를 output.txt에 출력하시오. n은 
20 이하의 양의 정수이다. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc != 3)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	FILE *infile, *outfile;
	int* arr, n, sum = 0;

	infile = fopen(argv[1], "r");
	if (infile==NULL)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	fscanf(infile, "%d", &n);
	if (n<=0 || n>20) // n은 20 이하의 양의 정수
	{
		fprintf(stderr, "잘못된 입력입니다.");
		fclose(infile);
		return 1;
	}

	arr = (int*)malloc(n * sizeof(int)); // 동적 할당

	for (int i = 0; i < n; i++) {
		fscanf(infile, "%d", &arr[i]); // 배열 읽어오기
		sum += arr[i]; // 덧셈 진행
	}

	fclose(infile);

	outfile = fopen(argv[2], "w");
	if (outfile==NULL)
	{
		fprintf(stderr, "Error");
		free(arr);
		return 1;
	}
	fprintf(outfile, "%d\n", sum);

	fclose(outfile);

	free(arr);

	return 0;
}