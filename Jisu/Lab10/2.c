#include <stdio.h>
#include <math.h>
#define MAX 16

typedef struct node *nodePointer;
typedef struct node {
    int num;
    nodePointer lLink;
    nodePointer rLink;
} node;


int main(int ac, char* av[]) {
    FILE* inf;
	int n, i = 0, data;
    node binTree[MAX];
    binTree[0].num = -1;
    binTree[0].lLink = NULL;
    binTree[0].rLink = NULL;
    for (i = 1; i < MAX; i++) {
        binTree[i].num = -1;
        binTree[i].lLink = NULL;
        binTree[i].rLink = NULL;
    }
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d ", &n);
    i = 1;
    while(!feof(inf)) {
        fscanf(inf, "%d", &binTree[i].num);
        if (i > 0) {
            if (binTree[i / 2].lLink == NULL) {
                binTree[i / 2].lLink = &binTree[i++];
            }
            else binTree[i / 2].rLink = &binTree[i++];
        }
    }
    int sum = 1;
    for (int j = 0; sum < i; j++) {
        sum += pow(2, j);
        for (int k = sum - pow(2, j); k < sum && k < i; k++)
            printf("%d ", binTree[k].num);
        printf("\n");
    }
    return 0;
}