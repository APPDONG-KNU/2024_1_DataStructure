#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;
    int expon;
    polyPointer* list;
} polyNode;
polyPointer a = NULL, b = NULL;

void attach(polyPointer* start, int coef, int expon) {
    polyPointer newNode = (polyPointer)malloc(sizeof(*newNode));
    newNode->coef = coef;
    newNode->expon = expon;

    if (*start == NULL) {
        *start = newNode;
        (*start)->list = newNode;
    }
    else {
        polyPointer current = *start;
        while (current->list != *start) {
            current = current->list;
        }
        current->list = newNode;
        newNode->list = *start;
    }
}

void addP(polyPointer* ptr, int coefficient, int expononent) {
    polyPointer temp;
    temp = (polyPointer)malloc(sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = expononent;
    (*ptr)->list = temp;
    *ptr = temp;
}

void printPolynomial(polyPointer start, FILE* outfile) {
    polyPointer current = start->list;
    do {
        fprintf(outfile, "%d %d\n", current->coef, current->expon);
        current = current->list;
    } while (current != start);
    fprintf(outfile, "\n");
}

int main(int argc, char* argv[]) {
    FILE* infile = fopen(argv[1], "r");
    FILE* outfile = fopen(argv[2], "w");

    int n, m;
    fscanf(infile, "%d %d", &n, &m);

    polyPointer startA = NULL, startB = NULL, c = NULL, lastC = NULL;
    attach(&a, 0, -1);
    attach(&b, 0, -1);

    for (int i = 0; i < n; ++i) {
        int coef, expon;
        fscanf(infile, "%d %d", &coef, &expon);
        attach(&a, coef, expon);
    }

    startA = a;
    a = a->list;

    for (int i = 0; i < m; ++i) {
        int coef, expon;
        fscanf(infile, "%d %d", &coef, &expon);
        attach(&b, coef, expon);
    }

    startB = b;
    b = b->list;

    c = (polyPointer)malloc(sizeof(*c));
    c->expon = -1;
    lastC = c;

    int sum, done = 0;
    while (done != 1) {
        switch ((a->expon == b->expon) ? 0 : ((a->expon < b->expon) ? -1 : 1)) {
        case -1:
            addP(&lastC, b->coef, b->expon);
            b = b->list;
            break;
        case 0:
            if (startA == a)
                done = 1;
            else {
                sum = a->coef + b->coef;
                if (sum)
                    addP(&lastC, sum, a->expon);

                a = a->list;
                b = b->list;
            }
            break;
        case 1:
            addP(&lastC, a->coef, a->expon);
            a = a->list;
            break;
        }
    } lastC->list = c;
    
    printPolynomial(c, outfile);

    fclose(infile);
    fclose(outfile);

    return 0;
}
