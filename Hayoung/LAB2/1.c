#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void add(int** A, int** B, int** C, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int** mal(int n, int m) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL) {
        fprintf(stderr, "Error");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Error");
            exit(1);
        }
    }
    return matrix;
}


int main(int argc, char* argv[]) {
    int** A, ** B, ** C;
    int n, m;

    FILE* infile, * outfile;

    infile = fopen(argv[1], "r");
    fscanf(infile, "%d", &n);
    fscanf(infile, "%d", &m);

    A = mal(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            fscanf(infile, "%d", &A[i][j]);
        }
    };
    
    B = mal(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            fscanf(infile, "%d", &B[i][j]);
        }
    };

    fclose(infile);

    C = mal(n, m);

    add(A, B, C, n, m);

    outfile = fopen(argv[2], "w");
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(outfile, "%d", C[i][j]);
            if (j < m - 1) {
                fprintf(outfile, " ");
            }
        }
        fprintf(outfile, "\n");
    }

    fclose(outfile);

    return 0;
}
