#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

//typedef struct node *nodePointer;
typedef struct node {
    int num;
    int lLink;
    int rLink;
} node;

int main(int ac, char* av[]) {
    FILE* inf;
	int n, i = 1, num, sum = 1;
    node* binTree;
    MALLOC(binTree, sizeof(node));
    binTree[0].num = -1;
    binTree[0].lLink = 0;
    binTree[0].rLink = 0;

	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d ", &n);
    while(!feof(inf)) {
        fscanf(inf, "%d", &num);
        if (i % 2) {
            binTree = (node*)realloc(binTree, sizeof(node) * (i + 1));
            binTree[i].num = num;
            binTree[i / 2].rLink = i++;
        }
        else {
            binTree = (node*)realloc(binTree, sizeof(node) * (i + 1));
            binTree[i].num = num;
            binTree[i / 2].lLink = i++;
        }
    }

    printf("%d \n", binTree[1].num);
    
    for (int j = 0; sum < i; j++) {
        sum += pow(2, j);
        for (int k = sum - pow(2, j); k < sum && k < i; k++) {
            printf("%d ", binTree[binTree[k].lLink].num);
            printf("%d ", binTree[binTree[k].rLink].num);
        }
        printf("\n");
    }

    return 0;
}