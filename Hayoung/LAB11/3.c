#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 20

typedef struct node* treePointer;
typedef struct node {
    char data;
    treePointer leftChild, rightChild;
} node;

node nodes[MAX_NODES + 1];

int nodeIndex = 0;

void inorder(treePointer ptr) {
    if (ptr && ptr->data != 'N')
    {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr) {
    if (ptr && ptr->data != 'N')
    {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}

void preorder(treePointer ptr) {
    if (ptr && ptr->data != 'N')
    {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

node* createNode(char data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

node* createBinaryTree(char arr[], int index) {
    node* root = NULL;
    if (arr[index] != 'N' && index < MAX_NODES + 1) {
        root = createNode(arr[index]);
        root->leftChild = createBinaryTree(arr, 2 * index);
        root->rightChild = createBinaryTree(arr, 2 * index + 1);
    }
    return root;
}

int main(int argc, char* argv[]) {
    FILE* infile = fopen(argv[1], "r");

    int num, i;
    fscanf(infile, "%d ", &num);

    char arr[MAX_NODES + 1];
    for (int i = 0; i < MAX_NODES + 1; i++)
        arr[i] = 'N';

    i = 1;
    while (!feof(infile)) {
        fscanf(infile, "%c ", &arr[i++]);
    }

    fclose(infile);

    node* root = createBinaryTree(arr, 1);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    return 0;
}
