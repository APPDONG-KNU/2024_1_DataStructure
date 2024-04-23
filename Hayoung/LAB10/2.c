#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODES 15

typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

node nodes[MAX_NODES];

int nodeIndex = 0;

node* createNode(int data) {
    if (nodeIndex >= MAX_NODES) {
        fprintf(stderr, "Maximum number of nodes reached\n");
        return NULL;
    }
    node* newNode = &nodes[nodeIndex++];
    newNode->data = data;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

node* createBinaryTree(int arr[], int index, int size) {
    node* root = NULL;
    if (index < size) {
        root = createNode(arr[index]);
        root->leftChild = createBinaryTree(arr, 2 * index + 1, size);
        root->rightChild = createBinaryTree(arr, 2 * index + 2, size);
    }
    return root;
}

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");

    int num = 0;
    fscanf(file, "%d", &num);

    int arr[MAX_NODES];

    int size = 0;
    int index = 0;
    while (fscanf(file, "%d", &arr[index]) == 1) {
        printf("%d ", arr[index]);

        if (arr[index] != -1)
            size++;        
        
        if (size > num)
            break;

        index++;
    }
    fclose(file);

    node* root = createBinaryTree(arr, 0, index);

    return 0;
}
