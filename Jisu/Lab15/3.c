#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

typedef struct tree* treePointer;
typedef struct tree {
    char data;
    treePointer l;
    treePointer r;
} tree;

char preorder[100];
char inorder[100];

treePointer createNode(char item) {
    treePointer lt;
    MALLOC(lt, sizeof(tree));
    lt->data = item;
    lt->l = NULL;
    lt->r = NULL;

    return lt;
}

treePointer buildTopology(int preStart, int inStart, int inEnd) {
    if (preStart >= strlen(preorder) || inStart > inEnd) return NULL;

    treePointer lt = createNode(preorder[preStart]);

    int rootInd;
    for (rootInd = inStart; rootInd <= inEnd; rootInd++)
        if (inorder[rootInd] == preorder[preStart]) break;

    int leftSubtreeSize = rootInd - inStart;

    lt->l = buildTopology(preStart + 1, inStart, rootInd - 1);
    lt->r = buildTopology(preStart + leftSubtreeSize + 1, rootInd + 1, inEnd);

    return lt;
}

void Result(treePointer lt, int nodeNum, char* nodes) {
    if (lt) {
        nodes[nodeNum - 1] = lt->data;
        Result(lt->l, nodeNum * 2, nodes);
        Result(lt->r, nodeNum * 2 + 1, nodes);
    }
}

int main(int ac, char* av[]) {
    FILE* f;

    f = fopen(av[1], "r");
    if (f == NULL) exit(1);

    fscanf(f, "preorder sequence : %s\n", preorder);
    fscanf(f, "inorder sequence : %s\n", inorder);

    fclose(f);

    int len = strlen(inorder);
    treePointer lt= buildTopology(0, 0, len - 1);

    int size = pow(2, (strlen(preorder) + 1)) - 1;
    char* result;
    MALLOC(result, sizeof(char) * size);

    Result(lt, 1, result);

    f = fopen(av[2], "w");
    if (f == NULL) exit(1);

    int ind = 0;
    for (int i = 0; i < size; i++) {
        if (result[i] != '\0') {
            fprintf(f, "%d", i + 1);

            if (ind == len - 1) break;

            fprintf(f, ", ");
            ind++;
        }
    }

    fclose(f);
}