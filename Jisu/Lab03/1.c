#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

int avail = 0;

void attach(int terms[][2], int coef, int exp) {
    terms[avail][0] = coef;
    terms[avail++][1] = exp;
}

void padd(int terms[][2], int sA, int sB, int fB, int *fD) {
    int coef, fA = sB - 1, sD = fB + 1;
    avail = fB + 1;
    while (sA <= fA && sB <= fB)
        switch (COMPARE(terms[sA][1], terms[sB][1]))
        {
        case -1:
            attach(terms, terms[sB][0], terms[sB][1]);
            sB++;
            break;
        case 0:
            coef = terms[sA][0] + terms[sB][0];
            if (coef) attach(terms, coef, terms[sA][1]);
            sA++; sB++;
            break;
        case 1:
            attach(terms, terms[sA][0], terms[sA][1]);
            sA++;
            break;
        }
    for (; sA <= fA; sA++)
        attach(terms, terms[sA][0], terms[sA][1]);
    for (; sB <= fB; sB++)
        attach(terms, terms[sB][0], terms[sB][1]);
    *fD = avail - 1;
}

void printPoly(char* av, int terms[][2], int s, int f) {
    FILE* outf;
    if ((outf = fopen(av, "w")) == NULL) {
		printf("error1");
		exit(1);
	}
    for (int i = s; i <= f; i++)
        fprintf(outf, "%-5d %d\n", terms[i][0], terms[i][1]);
    fclose(outf);
}

int main(int ac, char* av[]) {
    FILE* inf;
    int n, m, finishD;
    int terms[20][2];
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
    fscanf(inf, "%d %d", &n, &m);
    int startD = n + m;
    for (int i = 0; i < n + m; i++)
        fscanf(inf, "%d %d", &terms[i][0], &terms[i][1]);
    fclose(inf);
    
    padd(terms, 0, n, n + m - 1, &finishD);
    
    printPoly(av[2], terms, startD, finishD);

    return 0;
}
