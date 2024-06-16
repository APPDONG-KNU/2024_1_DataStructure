#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

int main(int ac, char* av[]) {
    FILE *f;
    int *a, n, d, j, k = 0, p = 2;
    
    f = fopen(av[1], "r");
    if (f == NULL) {
        printf("Failed to open files\n");
        return 1;
    }
    
    fscanf(f, "%d", &n);
    MALLOC(a, sizeof(int) * (n + 1));
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        fscanf(f, "%d ", &d);
        j = ++k;
        while((j != 1) && (d < a[j / 2])) {
            a[j] = a[j / 2];
            j /= 2;
        }
        a[j] = d;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
        if (i == p - 1) {
            printf("\n");
            p *= 2;
        }
    }
    free(a);
    fclose(f);
    
    return 0;
}