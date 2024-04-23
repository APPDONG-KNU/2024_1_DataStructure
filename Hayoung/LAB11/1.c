#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODES 20

char tree[MAX_NODES + 1];
int num;

void inorder(int index) {
    if (index < MAX_NODES+1 && tree[index] != 'N') {
        inorder(index * 2);
        printf("%c", tree[index]);
        inorder(index * 2 + 1);
    }
}

void preorder(int index) {
    if (index < MAX_NODES+1 && tree[index] != 'N') {
        printf("%c", tree[index]);
        preorder(index * 2);
        preorder(index * 2 + 1);
    }
}

void postorder(int index) {
    if (index < MAX_NODES+1 && tree[index] != 'N') {
        postorder(index * 2);
        postorder(index * 2 + 1);
        printf("%c", tree[index]);
    }
}

int main(int argc, char* argv[]) {
    FILE* infile;
    infile = fopen(argv[1], "r");

    int num;
    fscanf(infile, "%d ", &num);

    for (int i = 0; i < MAX_NODES + 1; i++)
        tree[i] = 'N';

    int i = 1;
    while (!feof(infile)) {   
        fscanf(infile, "%c ", &tree[i]);
        i++;
    }
    
    printf("inorder traversal: ");
    inorder(1);
    printf("\n");

    printf("preorder traversal: ");
    preorder(1);
    printf("\n");

    printf("postorder traversal: ");
    postorder(1);
    printf("\n");

    fclose(infile);

    return 0;
}
