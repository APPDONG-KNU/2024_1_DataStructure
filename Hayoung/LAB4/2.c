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

void mult(term a[], term b[], term c[]) {
    c[0].row = a[0].row;
    c[0].col = b[0].col;
    c[0].value = 0;

    for (int i = 0; i < a[0].row; i++) {
        for (int j = 0; j < b[0].col; j++) {
            int sum = 0;
            for (int k = 1; k <= a[0].value; k++) {
                if (a[k].row == i && b[k].col == j) {
                    sum += a[k].value * b[k].value;
                }
            }
            if (sum != 0) {
                c[0].value++;
                int index = c[0].value;
                c[index].row = i;
                c[index].col = j;
                c[index].value = sum;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    FILE* infile1, * infile2, * outfile;
    term a[MAX_SIZE], b[MAX_SIZE], c[MAX_SIZE * MAX_SIZE];
    int numCol, numRow;

    if (argc != 4) {
        printf("Usage: %s input1.txt input2.txt output.txt\n", argv[0]);
        return 1;
    }

    infile1 = fopen(argv[1], "r");
    infile2 = fopen(argv[2], "r");
    outfile = fopen(argv[3], "w");

    if (!infile1 || !infile2 || !outfile) {
        printf("Error: Unable to open files.\n");
        return 1;
    }

    // Read matrix A
    fscanf(infile1, "%d", &numCol);
    numRow = numCol;

    a[0].row = numRow;
    a[0].col = numCol;
    a[0].value = 0;

    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            int value;
            fscanf(infile1, "%d", &value);
            if (value != 0) {
                a[0].value++;
                int index = a[0].value;
                a[index].row = i;
                a[index].col = j;
                a[index].value = value;
            }
        }
    }

    // Read matrix B
    fscanf(infile2, "%d", &numCol);
    numRow = numCol;

    b[0].row = numRow;
    b[0].col = numCol;
    b[0].value = 0;

    for (int i = 0; i < numRow; i++) {
        for (int j = 0; j < numCol; j++) {
            int value;
            fscanf(infile2, "%d", &value);
            if (value != 0) {
                b[0].value++;
                int index = b[0].value;
                b[index].row = i;
                b[index].col = j;
                b[index].value = value;
            }
        }
    }

    fclose(infile1);
    fclose(infile2);

    fastTranspose(b, b);
    mult(a, b, c);

    // Write the result to output file
    fprintf(outfile, "%d\n", c[0].value);
    for (int i = 1; i <= c[0].value; i++) {
        fprintf(outfile, "%d %d %d\n", c[i].row, c[i].col, c[i].value);
    }

    fclose(outfile);

    return 0;
}
