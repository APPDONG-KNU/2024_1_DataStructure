#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, temp) (temp = *x, *x = *y, *y = temp)
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }

void printArr(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void quickSort(int a[], int left, int right) {
    int pivot, i, j, temp;

    if (left < right) {
        i = left; j = right + 1;
        pivot = a[left];
        do {
            do i++; while (a[i] < pivot);
            do j--; while (a[j] > pivot);
            if (i < j) SWAP(&a[i], &a[j], temp);
        } while (i < j);
        SWAP(&a[left], &a[j], temp);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (!f) exit(1);

    int size, *arr;
    fscanf(f, "%d", &size);
    MALLOC(arr, sizeof(int) * size);

    for (int i = 0; i < size; i++)
        fscanf(f, "%d ", &arr[i]);
    
    fclose(f);
    
    quickSort(arr, 0, size - 1);
    printArr(arr, size);
    free(arr);

    return 0;
}