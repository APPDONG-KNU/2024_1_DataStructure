#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 20

typedef struct {
    int row;
    int col;
    int value;
} term;

void fastTranspose(term a[], term b[]) {

    int rowTerms[MAX_SIZE], startingPos[MAX_SIZE];
    int i, j, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    for (i = 0; i < a[0].col; i++) {
        rowTerms[i] = 0;
    }
    for (i = 1; i <= a[0].value; i++) {
        rowTerms[a[i].col]++;
    }
    startingPos[0] = 1;

    for (i = 1; i < a[0].col; i++) {
        startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
    }

    for (i = 1; i <= a[0].value; i++) {
        j = startingPos[a[i].col]++;
        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }
}

int main(int argc, char *argv[]) {
    FILE* infile, * outfile;
    term a[MAX_SIZE], b[MAX_SIZE];
    int numCol, numRow;

    infile = fopen(argv[1], "r");

    fscanf(infile, "%d", &numCol);
    numRow = numCol;

    a[0].row = numRow;
    a[0].col = numCol;
    a[0].value = 0;

    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            int value;
            fscanf(infile, "%d", &value);
            if (value != 0) {
                a[0].value++;
                a[a[0].value].row = i;
                a[a[0].value].col = j;
                a[a[0].value].value = value;
            }
        }
    }

    fclose(infile);

    fastTranspose(&a, &b);

    outfile = fopen(argv[2], "w");

    fprintf(outfile, "%d\n", b[0].value);
    for (int i = 1; i <= b[0].value; i++) {
        fprintf(outfile, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
    }

    fclose(outfile);

    return 0;
}
