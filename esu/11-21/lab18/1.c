#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

void swap(element* a, element* b) {
    element temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(element a[], int left, int right) {
    int pivot, i, j;
    if (left < right) {
        i = left;
        j = right + 1;
        pivot = a[left].key;
        do {
            do { i++; } while (i <= right && a[i].key < pivot);
            do { j--; } while (a[j].key > pivot);
            if (i < j) {
                swap(&a[i], &a[j]);
            }
        } while (i < j);
        swap(&a[left], &a[j]);
        quickSort(a, left, j - 1);
        quickSort(a, j + 1, right);
    }
}

void printArray(element arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i].key);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if (in == NULL || out == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int n;
    fscanf(in, "%d", &n);

    element* arr = (element*)malloc(n * sizeof(element));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &arr[i].key);
    }

    printf("Unsorted array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);

    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i].key);
    }
    fprintf(out, "\n");

    free(arr);
    fclose(in);
    fclose(out);

    return 0;
}
