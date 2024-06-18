#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treePointer;
typedef struct tree {
    treePointer left;
    int data;
    treePointer right;
}tree;

typedef struct {
    int data;
    int left;
    int right;
} term;

void printTree(treePointer root, int level) {
    if (root != NULL) {
        printTree(root->right, level + 1);

        for (int i = 0; i < level; i++) {
            printf("    ");
        }

        printf("%d\n", root->data);

        printTree(root->left, level + 1);
    }
}
treePointer copy(term* original, int avail, int ptr);
treePointer makeBT(FILE* f);
int equal(treePointer t1, treePointer t2);

int i;

int main(int argc, char *argv[]) {
    FILE* f = fopen(argv[2], "r");
    if (f == NULL) exit(1);
    treePointer t1 = makeBT(f);

    f = fopen(argv[3], "r");
    if (f == NULL) exit(1);
    treePointer t2 = makeBT(f);

    int check = equal(t1, t2);

    printTree(t2, 0);

    if (check) {
        printf("they are same\n");
    }
    else {
        printf("they are different\n");
    }
}

treePointer copy(term* original, int avail, int ptr) {
    if (ptr <= avail && original[ptr].data != -1) {
        treePointer temp = (treePointer)malloc(sizeof(tree));
        temp->left = copy(original, avail, 2 * ptr);
        temp->right = copy(original, avail, 2 * ptr + 1);
        temp->data = original[ptr].data;

        return temp;
    }
    else
        return NULL;
}

treePointer makeBT(FILE* f) {
    int avail;
    fscanf(f, "%d\n", &avail);
    avail++;
    term* temp = (term*)malloc(sizeof(term) * avail);

    int ind = 1;
    int data;
    while (!feof(f)) {
        fscanf(f, "%d ", &data);
        temp[ind].data = data;
        temp[ind].left = -1;
        temp[ind].right = -1;

        if (data != -1) {
            if (ind % 2) temp[ind / 2].right = ind;
            else temp[ind / 2].left = ind;
        }
        else {
            avail++;
            temp = (term*)realloc(temp, sizeof(term) * avail);
        }
        ind++;
    }

    fclose(f);
    avail--;
    treePointer bt = copy(temp, avail, 1);

    return bt;
}

int equal(treePointer t1, treePointer t2) {
    return ((!t1 && !t2) || (t1 && t2 && (t1->data == t2->data) && equal(t1->left, t2->left) && equal(t1->right, t2->right)));
}


