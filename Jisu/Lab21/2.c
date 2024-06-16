#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct node* nodePointer;
typedef struct node {
    int data;
    int bf;
    nodePointer left;
    nodePointer right;
} node;

typedef struct qNode {
    nodePointer node;
    int index;
} qNode;

nodePointer createNode(int item) {
    nodePointer new;
    MALLOC(new, sizeof(node));
    new->data = item;
    new->bf = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

int height(nodePointer n) {
    if (n == NULL)
        return 0;
    int lh = height(n->left), rh = height(n->right);

    n->bf = lh - rh;  

    return (lh > rh ? lh : rh) + 1;
}

nodePointer rotateL(nodePointer x) {
    nodePointer y = x->right;
    x->right = y->left;
    y->left = x;

    height(x);
    height(y);

    return y;  
}

nodePointer rotateR(nodePointer y) {
    nodePointer x = y->left;
    y->left = x->right;
    x->right = y;

    height(x);
    height(y);

    return x;  
}

nodePointer insertNode(nodePointer root, nodePointer item) {
    if (root) {
        if (root->data >= item->data) root->left = insertNode(root->left, item);
        else root->right = insertNode(root->right, item);
    } else root = item;

    height(root);

    if (root->bf > 1) {
        if (item->data < root->left->data)
            return rotateR(root);  
        else {
            root->left = rotateL(root->left); 
            return rotateR(root);
        }
    }
    if (root->bf < -1) {
        if (item->data > root->right->data)
            return rotateL(root);  
        else {
            root->right = rotateR(root->right);  
            return rotateL(root);
        }
    }
    return root;
}

void add(qNode *queue, int *rear, nodePointer item, int index) {
    queue[++(*rear)].node = item;
    queue[*rear].index = index;
}

qNode delete(qNode *queue, int *front, int rear) {
    qNode temp;
    temp.node = NULL;
    if (rear != *front)
        temp = queue[++(*front)];

    return temp;
}

int main(int ac, char* av[]) {
    FILE *f = fopen(av[1], "r");
    if (!f) exit(1);

    int n, i, key, rear = -1, front = -1;
    nodePointer avl = NULL;
    qNode *queue, temp;
    fscanf(f, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(f, "%d", &key);
        avl = insertNode(avl, createNode(key));
    }

    fclose(f);

    MALLOC(queue, sizeof(qNode) * n);

    f = fopen(av[2], "w");
    if (!f) exit(1);

    i = 1;

    add(queue, &rear, avl, i);

    while(rear != front) {
        temp = delete(queue, &front, rear);
        if (!temp.node) break;  
        
        fprintf(f, "CBT %d번 노드 = %d \t bf = %d\n", temp.index, temp.node->data, temp.node->bf);

        if (temp.node->left) add(queue, &rear, temp.node->left, temp.index*2);
        if (temp.node->right) add(queue, &rear, temp.node->right, temp.index*2+1);
    }
    fclose(f);

    return 0;
}