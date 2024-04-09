#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    int col;
    int row;
    int value;
} term;

void transpose(term a[], term b[]) {
    int rowTerms[20];
    int startingPos[20];
    int i, j;
    int numCol = a[0].col;
    int numTerms = a[0].value;

    b[0].row = numCol;
    b[0].col = a[0].row;
    b[0].value = numTerms;

    if (numTerms > 0) {
        for (i = 0; i < numCol; i++)
            rowTerms[i] = 0;
        for (i = 1; i <= numTerms; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
        for (i = 1; i < numCol; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (i = 1; i <= numTerms; i++) {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int main(int ac, char* av[]) {
    FILE* inf, * outf;
    term a[401], b[401], c[401], r[401];
    int n, i, j, k, p, q;
    if ((inf = fopen(av[1], "r")) == NULL) {
        printf("error1");
        return 1;
    }
    fscanf(inf, "%d ", &n);

    a[0].row = n;
    a[0].col = n;
    a[0].value = 0;
    
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fscanf(inf, "%d ", &k);
            if (k != 0) {
                a[0].value++;
                a[a[0].value].row = i;
                a[a[0].value].col = j;
                a[a[0].value].value = k;
            }
        }

    fclose(inf);

    if ((inf = fopen(av[2], "r")) == NULL) {
        printf("error1");
        return 1;
    }
    fscanf(inf, "%d ", &n);

    c[0].row = n;
    c[0].col = n;
    c[0].value = 0;
    
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            fscanf(inf, "%d ", &k);
            if (k != 0) {
                c[0].value++;
                c[c[0].value].row = i;
                c[c[0].value].col = j;
                c[c[0].value].value = k;
            }
        }
    fclose(inf);

    transpose(c, b);
    
    r[0].row = n;
    r[0].col = n;
    r[0].value = 0;

    for (p = 0; p < n; p++)
        for (q = 0; q < n; q++) {
            int sum = 0;
            for (i = 0; i < n; i++)
                for (j = 1; j <= a[0].value; j++)
                    if (a[j].row == p && a[j].col == i)
                        for (k = 1; k <= b[0].value; k++)
                            if (b[k].row == q && b[k].col == i)
                                sum += a[j].value * b[k].value;
            if (sum != 0) {
                r[0].value++;
                r[r[0].value].row = p;
                r[r[0].value].col = q;
                r[r[0].value].value = sum;
            }
        }

    if ((outf = fopen(av[3], "w")) == NULL) {
        printf("error2");
        return 1;
    }
    
    fprintf(outf, "%d\n", r[0].value);

    for (int i = 1; i <= r[0].value; i++) {
        fprintf(outf, "%-4d ", r[i].row);
        fprintf(outf, "%-4d ", r[i].col);
        fprintf(outf, "%-4d\n", r[i].value);
    }

    fclose(outf);

    return 0;
}