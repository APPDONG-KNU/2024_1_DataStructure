#include <stdio.h>
#include <stdlib.h>
#define MAX 21

FILE *f;

void inorder(char tree[], int ptr) {
    if (ptr == 1) fprintf(f, "inorder traversal: ");
    if  (ptr < MAX && tree[ptr] != 'N') {
        inorder(tree, ptr * 2);
        fprintf(f, "%c", tree[ptr]);
        inorder(tree, ptr * 2 + 1);
    }
}

void preorder(char tree[], int ptr) {
    if (ptr == 1) fprintf(f, "preorder traversal: ");
    if  (ptr < MAX && tree[ptr] != 'N') {
        fprintf(f, "%c", tree[ptr]);
        preorder(tree, ptr * 2);
        preorder(tree, ptr * 2 + 1);
    }
}

void postorder(char tree[], int ptr) {
    if (ptr == 1) fprintf(f, "postorder traversal: ");
    if  (ptr < MAX && tree[ptr] != 'N') {
        postorder(tree, ptr * 2);
        postorder(tree, ptr * 2 + 1);
        fprintf(f, "%c", tree[ptr]);
    }
}

int main(int ac, char* av[]) {
    char tree[MAX];
    int ind = 1;

    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    int num;
    fscanf(f, "%d\n", &num);

    for (int i = 0; i < MAX; i++)
        tree[i] = 'N';
    
    while(!feof(f))
        fscanf(f, "%c ", &tree[ind++]);

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