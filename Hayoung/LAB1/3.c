/* 파일 input.txt에서 정수 n개와 임의의 수 m을 입력받고, Binary Search를 수행하여 n개
의 정수 중 m이 위치한 index 값을 output.txt에 출력하는 프로그램을 작성하시오. 단, n은 
0이 아닌 10이하의 정수이며, iterative 방식으로 코드를 작성해야 하고, 입력받은 n개의 정
수 중 m이 포함되지 않는 경우 –1을 출력한다. */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// binary search 이진 탐색 함수
int bs(int arr[], int n, int m) {
	int left = 0;
	int right = n-1;

	while (left <= right) // iterative -> while문 사용
	{
		int t = left + (right - left) / 2;
		if (arr[t] == m)
			return t; // m이 위치한 index
		else if (arr[t] < m)
			left = t + 1; // 왼쪽 부분 제외
		else
			right = t - 1; // 오른쪽 부분 제외
	}

	return -1; // 배열 arr에 m이 포함되지 않는 경우
}

int main(int argc, char *argv[]) {
	FILE* infile, * outfile;
	int n, m, i;
	int arr[10];

	infile = fopen(argv[1], "r");
	if (infile==NULL)
	{
		fprintf(stderr, "Error");
		return 1;
	}

	fscanf(infile, "%d %d", &n, &m);
	if (n<=0 || n>10)
	{
		fprintf(stderr, "Error");
		fclose(infile);
		return 1;
	}

	for ( i = 0; i < n; i++)
	{
		fscanf(infile, "%d", &arr[i]);
	}

	fclose(infile);

	int index = bs(arr, n, m);

	outfile = fopen(argv[2], "w");

	fprintf(outfile, "%d\n", index);

	fclose(outfile);

	return 0;
}