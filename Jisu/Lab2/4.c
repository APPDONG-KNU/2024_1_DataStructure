#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct {
    int accountNum;
    char name[30];
    int deposit;
    int loan;
} account;

void freeAry(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

int main(int ac, char* av[]) {
	FILE* inf, *outf;
	int n = 0;
	inf = fopen(av[1], "r");
	if (inf == NULL) {
		printf("error1");
		return 1;
	}
    while(1) {
        char input[100];
        char* pStr = fgets(input, 100, inf);
        if (pStr == NULL) break;
        n++;
    }
    fclose(inf);

	inf = fopen(av[1], "r");
	if (inf == NULL) {
		printf("error1");
		return 1;
	}
	account* a;
    MALLOC(a, sizeof(account) * n);
	if (a == NULL)
		exit(1);
	for (int i = 0; i < n; i++) {
		fscanf(inf, "%d %s %d %d ", &a[i].accountNum, &a[i].name, &a[i].deposit, &a[i].loan);
	}
	fclose(inf);
	
    int max = 0;
    for (int i = 1; i < n; i++)
        if (a[i].loan > a[max].loan) max = i;

	outf = fopen(av[2], "w");
	if (outf == NULL) {
		printf("error2");
		return 1;
	}
    fprintf(outf, "%d %s %d %d", a[max].accountNum, a[max].name, a[max].deposit, a[max].loan);
	free(a);
	fclose(outf);

	return 0;
}
