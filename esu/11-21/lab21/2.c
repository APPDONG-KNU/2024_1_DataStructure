#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct node* nodePointer;
typedef struct node {
    int data;
    int bf;
    nodePointer left; nodePointer right;
} node;

typedef struct qNode {
    nodePointer node;
    int index;
} qNode;


nodePointer createNode(int item);
nodePointer rotateRight(nodePointer y);
nodePointer rotateLeft(nodePointer x);
int height(nodePointer n);
nodePointer insertNode(nodePointer root, nodePointer item);
void add(qNode* queue, int* rear, nodePointer item, int index);
qNode delete(qNode* queue, int* front, int rear);


int main(int argc,char* argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (!f) exit(1);

    int n;
    fscanf(f, "%d", &n);

    nodePointer avl = NULL;

    int i, key;
    for (i = 0; i < n; i++) {
        fscanf(f, "%d", &key);
        avl = insertNode(avl, createNode(key));
    }

    fclose(f);

    qNode* queue = (qNode*)malloc(sizeof(qNode) * n);
    int rear = -1, front = -1;

    f = fopen(argv[2], "w");
    if (!f) exit(1);

    qNode temp;
    i = 1;

    add(queue, &rear, avl, i);

    while (rear != front) {
        temp = delete(queue, &front, rear);

        if (!temp.node) break;

        fprintf(f, "CBT %d¹ø ³ëµå = %d bf = %d\n", temp.index, temp.node->data, temp.node->bf);

        if (temp.node->left) add(queue, &rear, temp.node->left, temp.index * 2);
        if (temp.node->right) add(queue, &rear, temp.node->right, temp.index * 2 + 1);
    }

    fclose(f);
}


nodePointer createNode(int item) {
    nodePointer new = (nodePointer)malloc(sizeof(node));
    new->data = item;
    new->bf = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}


nodePointer rotateRight(nodePointer y) {
    nodePointer x = y->left;
    y->left = x->right;
    x->right = y;

    height(y);
    height(x);

    return x;
}

nodePointer rotateLeft(nodePointer x) {
    nodePointer y = x->right;
    x->right = y->left;
    y->left = x;

    height(x);
    height(y);

    return y;
}

int height(nodePointer n) {
    if (n == NULL)
        return 0;
    int lh = height(n->left);
    int rh = height(n->right);

    n->bf = lh - rh;

    return (lh > rh ? lh : rh) + 1;
}


nodePointer insertNode(nodePointer root, nodePointer item) {
    if (root) {
        if (root->data >= item->data) root->left = insertNode(root->left, item);
        else root->right = insertNode(root->right, item);
    }
    else root = item;

    height(root);

    if (root->bf > 1) {
        if (item->data < root->left->data)
            return rotateRight(root);
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    if (root->bf < -1) {
        if (item->data > root->right->data)
            return rotateLeft(root);
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    return root;
}


void add(qNode* queue, int* rear, nodePointer item, int index) {
    queue[++(*rear)].node = item;
    queue[*rear].index = index;
}


qNode delete(qNode* queue, int* front, int rear) {
    qNode temp;
    temp.node = NULL;
    if (rear != *front) {
        temp = queue[++(*front)];
    }

    return temp;
}
