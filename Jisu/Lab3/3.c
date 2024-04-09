#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct {
    int coef;
    int exp;
} polynomial;
int avail = 0;

void attach(polynomial* terms, int coef, int exp) {
    terms = (polynomial*)realloc(terms, sizeof(polynomial) * (avail + 1));
    terms[avail].coef = coef;
    terms[avail++].exp = exp;
}

void padd(polynomial* terms, int sA, int sB, int fB, int *fD) {
    int coef, fA = sB - 1, sD = fB + 1;
    avail = fB + 1;
    while (sA <= fA && sB <= fB)
        switch (COMPARE(terms[sA].exp, terms[sB].exp))
        {
        case -1:
            attach(terms, terms[sB].coef, terms[sB].exp);
            sB++;
            break;
        case 0:
            coef = terms[sA].coef + terms[sB].coef;
            if (coef) attach(terms, coef, terms[sA].exp);
            sA++; sB++;
            break;
        case 1:
            attach(terms, terms[sA].coef, terms[sA].exp);
            sA++;
            break;
        }
    for (; sA <= fA; sA++)
        attach(terms, terms[sA].coef, terms[sA].exp);
    for (; sB <= fB; sB++)
        attach(terms, terms[sB].coef, terms[sB].exp);
    *fD = avail - 1;
}

void printPoly(char* av, polynomial* terms, int s, int f) {
    FILE* outf;
    if ((outf = fopen(av, "w")) == NULL) {
		printf("error1");
		exit(1);
	}
    for (int i = s; i <= f; i++)
        fprintf(outf, "%-5d %d\n", terms[i].coef, terms[i].exp);
    fclose(outf);
}

int main(int ac, char* av[]) {
    FILE* inf;
    int n, m, finishD;
    polynomial *terms;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    fscanf(inf, "%d %d", &n, &m);
    int startD = n + m;
    MALLOC(terms, sizeof(polynomial) * (n + m + 1));
    for (int i = 0; i < n + m; i++)
        fscanf(inf, "%d %d", &terms[i].coef, &terms[i].exp);
    fclose(inf);
    
    padd(terms, 0, n, n + m - 1, &finishD);
    
    printPoly(av[2], terms, startD, finishD);
    free(terms);

    return 0;
}