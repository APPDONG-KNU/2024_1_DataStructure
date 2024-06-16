#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

typedef struct tree* treePointer;
typedef struct tree{
    char data;
    treePointer l;
    treePointer r;
} tree;

typedef struct{
    char data;
    int l;
    int r;
} term;

FILE *f;
int avail;

treePointer copy(term* original, int ptr) {
    if (ptr <= avail && original[ptr].data != 'N') {
        treePointer temp;
        MALLOC(temp, sizeof(tree));
        temp->l = copy(original, 2 * ptr);
        temp->r = copy(original, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    } else
        return NULL;
}

void inorder(treePointer ptr) {
    if  (ptr) {
        inorder(ptr->l);
        fprintf(f, "%c", ptr->data);
        inorder(ptr->r);
    }
}

void push(treePointer* stack, int *top, treePointer item) {
    if (*top >= 100) {
        printf("stack is full\n");
        exit(1);
    } else {
        stack[++(*top)] = item;
    }
}

treePointer pop(treePointer *stack, int *top) {
    if (*top < 0) {
        return 0;
    } else {
        return stack[(*top)--];
    }
}

void Ipostorder(treePointer ptr) {
    treePointer stack[101];
    treePointer stack1[101];
    int top = -1;
    int top1 = -1;

    push(stack, &top, ptr);

    while(top >= 0) {
        ptr = pop(stack, &top);
        push(stack1, &top1, ptr);
        
        if (ptr->l) {
            push(stack1, &top, ptr->l);
        }
        if (ptr->r) {
            push(stack1, &top, ptr->r);
        }
    }

    while(top1 >= 0) {
        ptr = pop(stack1, &top1);
        fprintf(f, "%c", ptr->data);
    }
}

int main(int ac, char* av[]) {
    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d\n", &avail);

    term* temp;
    MALLOC(temp, sizeof(term) * avail);

    int i = 1;
    char data;
    while(!feof(f)) {
        fscanf(f, "%c ", &data);
        temp[i].data = data;
        temp[i].l = -1;
        temp[i].r = -1;

        if (data != 'N') {
            if (i % 2) temp[i / 2].r = i;
            else temp[i / 2].l = i;
        } else {
            avail++;
            temp = (term*)realloc(temp, sizeof(term) * avail);
        }
        i++;
    }
    fclose(f);

    treePointer tree = copy(temp, 1);

    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    fprintf(f, "iterative implementation of postorder traversal : ");
    Ipostorder(tree);

    fclose(f);
    free(temp);
    free(tree);
}