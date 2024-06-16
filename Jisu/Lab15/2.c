#include <stdio.h>
#include <stdlib.h>

int findRoot(int *eqv, int child) {
    while (child >= 0 && child < 100 && eqv[child] >= 0)
        child = eqv[child];
    return child;
}

void process(int *arr, int a, int b) {
    if (a < 0 || b < 0) return;

    if (arr[a] == 101)
        arr[a] = -1;

    if (arr[b] == 101)
        arr[b] = -1;

    if (arr[b] < arr[a]) {
        arr[a] = b;
        arr[b]--;
    } else if (arr[b] >= 0 && arr[a] < 0) {
        arr[a] = findRoot(arr, b);
        arr[findRoot(arr, b)]--;
    } else if (arr[b] >= arr[a]) {
        arr[b] = a;
        arr[a]--;
    } else if (arr[b] < 0 && arr[a] >= 0) {
        arr[b] = findRoot(arr, a);
        arr[findRoot(arr, a)]--;
    }
}

int main(int ac, char* av[]) {
    int n, arr[100];

    for (int i = 0; i < 100; i++)
        arr[i] = 101;

    FILE *f = fopen(av[1], "r");
    if (f == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (fscanf(f, "%d", &n) != 1) {
        perror("Error reading number of pairs");
        fclose(f);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        int a, b;
        if (fscanf(f, "%d = %d,", &a, &b) != 2) {
            perror("Error reading pairs");
            fclose(f);
            return EXIT_FAILURE;
        }
        process(arr, a, b);
    }

    fclose(f);

    int cnt = 0;
    for (int i = 0; i < 100; i++)
        if (arr[i] < 0) cnt++;

    f = fopen(av[2], "w");
    if (f == NULL) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    fprintf(f, "Total # of equivalence classes = %d\n", cnt);

    fprintf(f, "Equivalence classes: ");
    int bracketNum = 0;
    for (int i = 0; i < 100; i++)
        if (arr[i] < 0) {
            fprintf(f, "{%d", i);
            for (int j = 0; j < 100; j++)
                if (findRoot(arr, j) == i && j != i)
                    fprintf(f, ", %d", j);
            fprintf(f, "}");
            bracketNum++;
            if (bracketNum < cnt) fprintf(f, ", ");
        }

    fclose(f);
    return EXIT_SUCCESS;
}