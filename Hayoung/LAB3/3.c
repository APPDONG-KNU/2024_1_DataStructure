#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

struct polynomial {
    int coef;
    int exp;
};

void addPoly(struct polynomial poly[], int termCount1, struct polynomial poly2[], int termCount2, struct polynomial result[], int* resultCount) {
    int i = 0, j = 0, k = 0;

    while (i < termCount1 && j < termCount2) {
        if (poly[i].exp > poly2[j].exp) {
            result[k++] = poly[i++];
        }
        else if (poly[i].exp < poly2[j].exp) {
            result[k++] = poly2[j++];
        }
        else {
            result[k].coef = poly[i].coef + poly2[j].coef;
            result[k++].exp = poly[i].exp;
            i++;
            j++;
        }
    }

    // 남은 항들 추가
    while (i < termCount1) {
        result[k++] = poly[i++];
    }
    while (j < termCount2) {
        result[k++] = poly2[j++];
    }

    *resultCount = k;
}

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Error: Cannot open input file\n");
        return 1;
    }

    int termCount1 = 0, termCount2 = 0;
    struct polynomial poly1[MAX_TERMS], poly2[MAX_TERMS];

    fscanf(infile, "%d %d", &termCount1, &termCount2);

    for (int i = 0; i < termCount1; i++) {
        fscanf(infile, "\n%d %d", &poly1[i].coef, &poly1[i].exp);
    }

    for (int i = 0; i < termCount2; i++) {
        fscanf(infile, "\n%d %d", &poly2[i].coef, &poly2[i].exp);
    }

    fclose(infile);

    struct polynomial result[MAX_TERMS];
    int resultCount = 0;

    addPoly(poly1, termCount1, poly2, termCount2, result, &resultCount);

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error: Cannot open output file\n");
        return 1;
    }

    for (int i = 0; i < resultCount; i++) {
        fprintf(outfile, "%d %d\n", result[i].coef, result[i].exp);
    }

    fclose(outfile);

    return 0;
}
