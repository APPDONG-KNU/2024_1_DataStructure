#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct polyN *polyPointer;
typedef struct polyN {
    int coef;
    int expon;
    polyPointer link;
} polyN;

#define COMPARE(x, y) ((x) < (y) ? -1 : (x) == (y) ? 0 : 1)

polyPointer a = NULL, b = NULL, c = NULL, rear = NULL, temp = NULL;
int cnt = 0;

polyPointer createNode(int coef, int expon) {
    polyPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->link = NULL;
    cnt++;
    return newNode;
}

void readNums(char* av) {
    FILE* inf = fopen(av, "r");
    if (inf == NULL) {
		printf("error1");
		exit(1);
	}

    a = createNode(0, -1);
    b = createNode(0, -1);
    polyPointer tailA = a;
    polyPointer tailB = b;
    int n, m, co, ex;

    fscanf(inf, "%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        fscanf(inf, "%d %d", &co, &ex);
        polyPointer newNode = createNode(co, ex);
        tailA->link = newNode;
        tailA = newNode;
    }
    tailA->link = a;

    for (int i = 0; i < m; i++) {
        fscanf(inf, "%d %d", &co, &ex);
        polyPointer newNode = createNode(co, ex);
        tailB->link = newNode;
        tailB = newNode;
    }
    tailB->link = b;

    fclose(inf);
}

void calc() {
    int done = 0, sum;
    polyPointer startA = a, lastC = NULL, newNode;
    a = a->link;
    b = b->link;
    c = createNode(0, -1);
    do {
        switch (COMPARE(a->expon, b->expon)) {
        case -1:
            newNode = createNode(b->coef, b->expon);
            if (lastC == NULL) {
                lastC = newNode;
                c->link = newNode;
            } else {
                lastC->link = newNode;
                lastC = newNode;
            }
            b = b->link;
            break;
        case 0:
            if (startA == a) done = 1;
            else {
                sum = a->coef + b->coef;
                if (sum) {
                    newNode = createNode(sum, a->expon);
                    if (lastC == NULL) {
                        lastC = newNode;
                        c->link = newNode;
                    } else {
                        lastC->link = newNode;
                        lastC = newNode;
                    }
                }
                a = a->link; b = b->link;
            }
            break;
        case 1:
            newNode = createNode(a->coef, a->expon);
            if (lastC == NULL) {
                lastC = newNode;
                c->link = newNode;
            } else {
                lastC->link = newNode;
                lastC = newNode;
            }
            a = a->link;
        }
    } while (!done);
    lastC->link = c;
}

void printPoly(polyPointer poly, char* av) {
    FILE* outf = fopen(av, "w");
    if (outf == NULL) {
		printf("error1");
		exit(1);
	}
    polyPointer current = poly->link;
    while (current != poly) {
        fprintf(outf, "%-5d %d\n", current->coef, current->expon);
        current = current->link;
    }
    fprintf(outf, "\n");
    fclose(outf);
}

int main(int ac, char* av[]) {
    if (ac < 2) {
        printf("Usage: %s input_file\n", av[0]);
        return 1;
    }
    readNums(av[1]);
    calc();
    printPoly(c, av[2]);

    return 0;
}
