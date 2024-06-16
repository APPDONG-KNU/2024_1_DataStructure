#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

int *a;
int k = 0;

void adjust (int root, int size) {
    int child = 2 * root, temp = a[root];
    while(child <= size) {
        if ((child < size) && (a[child] < a[child + 1]))
            child++;
        if (temp > a[child]) break;
        else {
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

void heapSort() {
    int i, j, temp;

    for (i = k / 2; i > 0; i--)
        adjust(i, k);
    for(i = k - 1; i > 0; i--) {
        SWAP(a[1], a[i + 1], temp);
        adjust(1, i);
    }
}

int main(int ac, char* av[]) {
    FILE *f;
    int n, d, j, p = 2;
    
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
        while((j != 1) && (d > a[j / 2])) {
            a[j] = a[j / 2];
            j /= 2;
        }
        a[j] = d;
    }

    heapSort();

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    puts("");
    
    free(a);
    fclose(f);
    
    return 0;
}