#include <stdio.h>
#include <math.h>
#define MAX 16

int main(int ac, char* av[]) {
    FILE* inf;
	int n, i = 0, data, sum = 1;
    int binTree[MAX];
    for (i = 0; i < MAX; i++) binTree[i] = -1;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d ", &n);
    i = 1;
    while(!feof(inf))
        fscanf(inf, "%d", &binTree[i++]);

    for (int j = 0; sum < i; j++) {
        sum += pow(2, j);
        for (int k = sum - pow(2, j); k < sum && k < i; k++)
            printf("%d ", binTree[k]);
        printf("\n");
    }
    return 0;
}