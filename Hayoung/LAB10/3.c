#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
} node;

node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
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

    int* arr = (int*)malloc(num * sizeof(int));

    int size = 0, index = 0;
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

    free(root);

    return 0;
}
