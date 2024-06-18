#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree* treePointer;
typedef struct tree {
    treePointer left;
    int data;
    treePointer right;
} tree;

typedef struct {
    int data;
    int left;
    int right;
} term;

treePointer copy(term* original, int avail, int ptr);
treePointer makeBT(FILE* f);
void printTree(treePointer root, int depth);
void findNode(treePointer root, treePointer* target, int index);
void findParent(treePointer root, treePointer target, treePointer* parent);
void deleteNode(treePointer root, int data);

int i;
int target, avail;

int main(int argc,char* argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) exit(1);
    treePointer bt = makeBT(f);

    deleteNode(bt, target);

    printTree(bt, 0);

    return 0;
}

treePointer copy(term* original, int avail, int ptr) {
    if (ptr <= avail && original[ptr].data) {
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
    fscanf(f, "%d\n", &avail);
    avail++;
    term* temp = (term*)malloc(sizeof(term) * avail);

    int ind = 1;
    int data;
    char input[20];

    while (!feof(f)) {
        fscanf(f, "%s ", input);

        if (!strcmp(input, "-")) {
            break;
        }

        data = atoi(input);
        temp[ind].data = data;
        temp[ind].left = 0;
        temp[ind].right = 0;

        if (data) {
            if (ind % 2) temp[ind / 2].right = ind;
            else temp[ind / 2].left = ind;
        }
        else {
            avail++;
            temp = (term*)realloc(temp, sizeof(term) * avail);
        }
        ind++;
    }

    fscanf(f, "%d", &target);
    fclose(f);

    treePointer bt = copy(temp, avail, 1);

    return bt;
}

void printTree(treePointer root, int depth) {
    if (root == NULL) {
        return;
    }

    // Print right subtree
    printTree(root->right, depth + 1);

    // Indent according to depth
    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    // Print node data if non-zero
    if (root->data != -1) {
        printf("%d\n", root->data);
    }

    // Print left subtree
    printTree(root->left, depth + 1);
}

void findNode(treePointer root, treePointer* target, int index) {
    if (root == NULL) return;

    if (root->data == index) {
        *target = root;
        return;
    }

    findNode(root->left, target, index);
    findNode(root->right, target, index);
}

void findParent(treePointer root, treePointer target, treePointer* parent) {
    if (root == NULL) return;

    if (root->left == target || root->right == target) {
        *parent = root;
        return;
    }

    findParent(root->left, target, parent);
    findParent(root->right, target, parent);
}

void deleteNode(treePointer root, int data) {
    treePointer target = NULL;
    findNode(root, &target, data);
    if (target == NULL) return;

    treePointer parent = NULL;
    findParent(root, target, &parent);

    if (target->left == NULL && target->right == NULL) {
        if (parent == NULL) {
            free(target);
            return;
        }

        if (parent->left == target) parent->left = NULL;
        else parent->right = NULL;
        free(target);
    }
    else if (target->left == NULL || target->right == NULL) {
        if (parent == NULL) {
            if (target->left != NULL) root = target->left;
            else root = target->right;
            free(target);
            return;
        }

        treePointer child = target->left != NULL ? target->left : target->right;
        if (parent->left == target) parent->left = child;
        else parent->right = child;
        free(target);
    }
    else {
        treePointer minRight = target->right;
        while (minRight->left != NULL) {
            minRight = minRight->left;
        }
        target->data = minRight->data;
        deleteNode(target->right, minRight->data);
    }
}
