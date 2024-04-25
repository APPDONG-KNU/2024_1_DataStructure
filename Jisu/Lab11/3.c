#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

FILE *f;

typedef struct{
    char data;
    int lc;
    int rc;
} node;

void inorder(node* tree, int ptr) {
    if (ptr == 1) fprintf(f, "inorder traversal: ");
    if  (ptr != -1) {
        inorder(tree, tree[ptr].lc);
        fprintf(f, "%c", tree[ptr].data);
        inorder(tree, tree[ptr].rc);
    }
}

void preorder(node* tree, int ptr) {
    if (ptr == 1) fprintf(f, "preorder traversal: ");
    if  (ptr != -1) {
        fprintf(f, "%c", tree[ptr].data);
        preorder(tree, tree[ptr].lc);
        preorder(tree, tree[ptr].rc);
    }
}

void postorder(node* tree, int ptr) {
    if (ptr == 1) fprintf(f, "postorder traversal: ");
    if  (ptr != -1) {
        postorder(tree, tree[ptr].lc);
        postorder(tree, tree[ptr].rc);
        fprintf(f, "%c", tree[ptr].data);
    }
}

int main(int ac, char* av[]) {
    node* tree;
    MALLOC(tree, sizeof(node));
    int ind = 1, num;

    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    fscanf(f, "%d\n", &num);

    tree[0].data = 'N';
    tree[0].lc = -1;
    tree[0].rc = -1;
    
    while(!feof(f)) {
        tree = (node*)realloc(tree, sizeof(node) * (ind + 1));
        fscanf(f, "%c ", &tree[ind].data);
        tree[ind].lc = -1;
        tree[ind].rc = -1;

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