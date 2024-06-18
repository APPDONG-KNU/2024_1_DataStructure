#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void push(int item);

int* minHeap;
int size = 0;
FILE* f;

int main(int argc, char* argv[]) {
    f = fopen(argv[1], "r");
    if (f == NULL) exit(1);

    int total;  //입력되는 수의 개수
    fscanf(f, "%d\n", &total);

    minHeap = (int*)malloc(sizeof(int) * total);

    int data;
    for (int i = 0; i < total; i++) {
        fscanf(f, "%d ", &data);
        push(data);
    }

    fclose(f);

    for (int i = 1; i <= size; i++) {
        printf("%d ", minHeap[i]);
    }
    puts("");
}

void push(int item) {
    int i = ++size;
    while ((i != 1) && (item < minHeap[i / 2])) {
        minHeap[i] = minHeap[i / 2];
        i /= 2;
    }
    minHeap[i] = item;
}