/* ������ ���� 0�� �ƴ� ���� ���� n�� ũ�⸦ ���ϴ� ������ ���� �迭�� ���� �޸� ��
���� �̿��Ͽ� ������ ��, ������ ���� ����� input.txt ���Ͽ��� n���� ������ �о� �迭�� 
�����Ͻÿ�. �׸��� �迭�� ����� �������� ��� ���� ����� output.txt�� ����Ͻÿ�. n�� 
20 ������ ���� �����̴�. */

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
	if (n<=0 || n>20) // n�� 20 ������ ���� ����
	{
		fprintf(stderr, "�߸��� �Է��Դϴ�.");
		fclose(infile);
		return 1;
	}

	arr = (int*)malloc(n * sizeof(int)); // ���� �Ҵ�

	for (int i = 0; i < n; i++) {
		fscanf(infile, "%d", &arr[i]); // �迭 �о����
		sum += arr[i]; // ���� ����
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