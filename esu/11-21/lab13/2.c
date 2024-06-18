#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 5
typedef enum { false, true, not, and, or } logical;
typedef struct tree* treePointer;
typedef struct tree {
    logical data;
    int value;
    treePointer left, right;
} tree;

void printTree(treePointer root, int depth);
treePointer createNode(int item);
treePointer copy(logical* arr, int size, int idx);
void evaluate(treePointer bt);

int main(int argc, char *argv[]) {
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        printf("Error opening input file\n");
        exit(1);
    }

    int vNum;
    fscanf(f, "%d\n", &vNum);

    logical* truthV = (logical*)malloc(sizeof(logical) * vNum);

    int i;
    char input[100];
    for (i = 0; i < vNum; i++) {
        fscanf(f, "%s ", input);
        if (!strcmp(input, "true") || !strcmp(input, "true,"))
            truthV[i] = true;
        else if (!strcmp(input, "false") || !strcmp(input, "false,"))
            truthV[i] = false;
    }

    logical arr[100];
    i = 1;
    while (!feof(f)) {
        fscanf(f, "%s ", input);
        if (!strcmp(input, "false")) arr[i] = false;
        else if (!strcmp(input, "true")) arr[i] = true;
        else if (!strcmp(input, "not")) arr[i] = not;
        else if (!strcmp(input, "and")) arr[i] = and;
        else if (!strcmp(input, "or")) arr[i] = or ;
        else if (!strcmp(input, "empty")) arr[i] = 5;
        else {
            arr[i] = truthV[input[1] - 48];
        }
        i++;
    }
    int size = i;

    fclose(f);

    treePointer bt = copy(arr, size, 1);

    // printf("Tree structure:\n");
     //printTree(bt, 0);

    evaluate(bt);

    if (bt->value == true) printf("Result: true\n");
    else printf("Result: false\n");

    // Free dynamically allocated memory
    free(truthV);

    return 0;
}

void printTree(treePointer root, int depth) {
    if (root == NULL) return;

    depth += COUNT;

    printTree(root->right, depth);

    printf("\n");
    for (int i = 0; i < depth + 1; i++) {
        printf(" ");
    }
    if (root->data == not) printf("%4s\n", "not");
    else if (root->data == and) printf("%4s\n", "and");
    else if (root->data == or) printf("%4s\n", "or");
    else if (root->data == true) printf("%4s\n", "true");
    else if (root->data == false) printf("%4s\n", "false");

    printTree(root->left, depth + 1);
}

treePointer createNode(int item) {
    treePointer new = (treePointer)malloc(sizeof(tree));
    new->data = item;
    new->left = NULL;
    new->right = NULL;

    return new;
}

treePointer copy(logical* arr, int size, int idx) {
    treePointer new = NULL;

    if (idx <= size - 1 && arr[idx] != 5) {
        new = createNode(arr[idx]);
        new->left = copy(arr, size, idx * 2);
        new->right = copy(arr, size, idx * 2 + 1);
    }

    return new;
}

void evaluate(treePointer bt) {
    if (bt) {
        evaluate(bt->left);
        evaluate(bt->right);

        switch (bt->data) {
        case false:
            bt->value = 0;
            break;
        case true:
            bt->value = 1;
            break;
        case not:
            bt->value = !(bt->right->value);
            break;
        case or :
            bt->value = bt->left->value || bt->right->value;
            break;
        case and :
            bt->value = bt->left->value && bt->right->value;
        }
    }
}
