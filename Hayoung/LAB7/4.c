#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACKS 10

typedef struct {
    int key;
} element;

typedef struct stack* stackPointer;
typedef struct stack {
    element data;
    stackPointer link;
} stack;

stackPointer top[MAX_STACKS];

void push(int i, element item) {
    stackPointer temp = (stackPointer)malloc(sizeof(stack));
    temp->data = item;
    temp->link = top[i];
    top[i] = temp;
}

element pop(int i) {
    stackPointer temp = top[i];
    element item = { 0 };
    if (!temp)
        return item;
    item = temp->data;
    top[i] = temp->link;
    free(temp);
    return item;
}

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    element item;

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    for (int i = 0; i < MAX_STACKS; i++) {
        top[i] = NULL;
    }

    while (fscanf(infile, "%d", &item.key) != EOF) {
        push(0, item);
    }
    
    while ((item = pop(0)).key != 0) {
        fprintf(outfile, "%d ", item.key);
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
