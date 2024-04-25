#include <stdio.h>
#include <stdlib.h>
#define MAX 21

FILE *f;

typedef struct{
    char data;
    int lc;
    int rc;
} node;

void inorder(node tree[], int ptr) {
    if (ptr == 1) fprintf(f, "inorder traversal: ");
    if  (ptr != -1) {
        inorder(tree, tree[ptr].lc);
        fprintf(f, "%c", tree[ptr].data);
        inorder(tree, tree[ptr].rc);
    }
}

void preorder(node tree[], int ptr) {
    if (ptr == 1) fprintf(f, "preorder traversal: ");
    if  (ptr != -1) {
        fprintf(f, "%c", tree[ptr].data);
        preorder(tree, tree[ptr].lc);
        preorder(tree, tree[ptr].rc);
    }
}

void postorder(node tree[], int ptr) {
    if (ptr == 1) fprintf(f, "postorder traversal: ");
    if  (ptr != -1) {
        postorder(tree, tree[ptr].lc);
        postorder(tree, tree[ptr].rc);
        fprintf(f, "%c", tree[ptr].data);
    }
}

int main(int ac, char* av[]) {
    node tree[MAX];
    int ind = 1;

    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d\n", &num);

    for (int i = 0; i < 20; i++) {
        tree[i].lc = -1;
        tree[i].rc = -1;
    }

    while(!feof(f)) {
        fscanf(f, "%c ", &tree[ind].data);

        if (tree[ind].data != 'N') {
            if (ind % 2) tree[ind / 2].rc = ind;
            else tree[ind / 2].lc = ind;
        }
        ind++;
    }

    fclose(f);

    f = fopen(av[2], "w");
    if (f == NULL)exit(1);

    inorder(tree, 1);
    fprintf(f, "\n");

    preorder(tree, 1);
    fprintf(f, "\n");

    postorder(tree, 1);    
    fprintf(f, "\n");

    fclose(f);
}