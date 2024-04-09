#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

void freeAry(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

int main(int ac, char* av[]) {
    FILE *inf, *outf;
    int n, m;
    char** a;
    char input[100];
    MALLOC(a, sizeof(char*) * 2);
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    for (int i = 0; i < 2; i++) {
        fgets(input, 100, inf);
        MALLOC(a[i], sizeof(input));
        strcpy(a[i], input);
    }
    fclose(inf);

    if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error2");
		return 1;
	}
	for (int i = 0; i < 2; i++) {
		fprintf(outf, "%s", a[i]);
	}
    fclose(outf);

    freeAry(a, 2);
    return 0;
}
