#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
	int n;
	if ((inf = fopen(av[1], "r")) == NULL) {
		printf("error1");
		return 1;
	}
	fscanf(inf, "%d ", &n);

    term a[401], b[401];
    int k;
    a[0].row = n;
    a[0].col = n;
    a[0].value = 0;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            fscanf(inf, "%d ", &k);
            if (k != 0) {
                a[0].value++;
                a[a[0].value].row = i;
                a[a[0].value].col = j;
                a[a[0].value].value = k;
            }
        }

	fclose(inf);

    transpose(a, b);

	if ((outf = fopen(av[2], "w")) == NULL) {
		printf("error2");
		return 1;
	}
	
    fprintf(outf, "%d\n", b[0].value);

    for (int i = 1; i <= b[0].value; i++) {
        fprintf(outf, "%-4d ", b[i].row);
        fprintf(outf, "%-4d ", b[i].col);
        fprintf(outf, "%-4d\n", b[i].value);
    }

	fclose(outf);

	return 0;
}