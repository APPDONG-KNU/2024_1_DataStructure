#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

int n, *a;

void makeBT(FILE* f, int* i) {
    int s;
    while (n != 0) {
        fscanf(f, "%d ", &s);
        printf("",s);
        n--;
        if (!s) {
            n++;
            a = (int*)realloc(a, sizeof(int) * ((*i) + 1));
        }
        a[*i] = s;
        (*i)++;
    }
}

int main(int ac, char* av[]) {
    FILE *f;
    int i = 1, j, d, k;
    char c, l;

    f = fopen(av[1], "r");
    if (f == NULL) {
        printf("Failed to open files\n");
        return 1;
    }
    
    fscanf(f, "%d", &n);
    MALLOC(a, sizeof(int) * (n + 1));
    
    makeBT(f, &i);
    fscanf(f, "%c %d %c %d", &c, &d, &l, &k);
    for (j = 1; j < i; j++)
        if (a[j] == d) break;
    if (l == 'L') a[j * 2] = k;
    else a[j * 2 + 1] = k;
    for (j = 1; j < i; j++) printf("%d ", a[j]);
    free(a);
    fclose(f);
    
    return 0;
}