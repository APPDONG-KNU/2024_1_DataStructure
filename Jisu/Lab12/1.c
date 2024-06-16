#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

typedef struct tree* treePointer;
typedef struct tree {
    char data;
    treePointer l;
    treePointer r;
} tree;

typedef struct {
    char data;
    int l;
    int r;
} term;

int avail;

treePointer copy(term* original, int ptr) {
    if (ptr <= avail && original[ptr].data != 'N') {
        treePointer temp;
        MALLOC(temp, sizeof(tree));
        temp->l = copy(original, 2 * ptr);
        temp->r = copy(original, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    } else {
        return NULL;
    }
}

void inorder(treePointer ptr, FILE* f) {
    if (ptr) {
        inorder(ptr->l, f);
        if (ptr->data != 'N') {
            fprintf(f, "%c", ptr->data);
        }
        inorder(ptr->r, f);
    }
}

int main(int ac, char* av[]) {
    FILE *f;
    
    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d\n", &avail);
    avail++;
    term* temp;
    MALLOC(temp, sizeof(term) * avail);
    
    int i = 1;
    char data;
    while (i <= avail) {
        fscanf(f, "%c ", &data);
        if (data == ' ')
            continue;
        temp[i].data = data;
        temp[i].l = -1;
        temp[i].r = -1;

        if (data != 'N') {
            fscanf(f, "%d %d\n", &temp[i].l, &temp[i].r);
        }

        i++;
    }

    fclose(f);
    avail--;

    treePointer tree = copy(temp, 1);

    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    fprintf(f, "recursive implementation of inorder traversal : ");
    inorder(tree, f);

    fclose(f);
    free(temp);
    free(tree);

    return 0;
}