#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* parent;
    int* rank;
    int size;
} UnionFind;

// Initialize the Union-Find structure
UnionFind* create_union_find(int size) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->parent = (int*)malloc(size * sizeof(int));
    uf->rank = (int*)malloc(size * sizeof(int));
    uf->size = size;
    for (int i = 0; i < size; ++i) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    return uf;
}

// Find with path compression
int find(UnionFind* uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

// Union by rank
void union_sets(UnionFind* uf, int x, int y) {
    int rootX = find(uf, x);
    int rootY = find(uf, y);

    if (rootX != rootY) {
        if (uf->rank[rootX] > uf->rank[rootY]) {
            uf->parent[rootY] = rootX;
        }
        else if (uf->rank[rootX] < uf->rank[rootY]) {
            uf->parent[rootX] = rootY;
        }
        else {
            uf->parent[rootY] = rootX;
            uf->rank[rootX]++;
        }
    }
}

// Free the Union-Find structure
void free_union_find(UnionFind* uf) {
    free(uf->parent);
    free(uf->rank);
    free(uf);
}
// Print the equivalence classes
void print_equivalence_classes(UnionFind* uf, FILE* output) {
    int* classes = (int*)malloc(uf->size * sizeof(int));
    for (int i = 0; i < uf->size; ++i) {
        classes[i] = find(uf, i);
    }

    int* printed = (int*)calloc(uf->size, sizeof(int));
    int num_classes = 0;



    for (int i = 0; i < uf->size; ++i) {
        if (!printed[i]) {
            int root = classes[i];
            int class_size = 0;
            for (int j = 0; j < uf->size; ++j) {
                if (classes[j] == root) {
                    printed[j] = 1;
                    class_size++;
                }
            }
            if (class_size > 1) {

                if (num_classes == 0) {
                    fprintf(output, "Equivalence classes : { ");
                }
                else {
                    fprintf(output, ", ");
                }
                fprintf(output, "{ ");
                int first_printed = 0;
                for (int j = 0; j < uf->size; ++j) {
                    if (classes[j] == root) {
                        if (first_printed) {
                            fprintf(output, ", ");
                        }
                        else {
                            first_printed = 1;
                        }
                        fprintf(output, "%d", j);
                    }
                }
                fprintf(output, " }");
                num_classes++;
            }

        }
    }
    fprintf(output, " }\n");
    fprintf(output, "Total # of equivalence classes = %d\n", num_classes);

    free(classes);
    free(printed);
}







int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    if (!input) {
        perror("Unable to open input file");
        return 1;
    }
    if (!output) {
        perror("Unable to open output file");
        fclose(input);
        return 1;
    }

    int n;
    fscanf(input, "%d", &n);
    printf("Total number of pairs: %d\n", n);

    int pairs[n][2];
    int max_element = -1;

    for (int i = 0; i < n; ++i) {
        fscanf(input, "%d = %d,", &pairs[i][0], &pairs[i][1]);
        printf("Pair %d: %d = %d\n", i + 1, pairs[i][0], pairs[i][1]);
        if (pairs[i][0] > max_element) max_element = pairs[i][0];
        if (pairs[i][1] > max_element) max_element = pairs[i][1];
    }

    fclose(input);

    // Create the Union-Find structure
    UnionFind* uf = create_union_find(max_element + 1);

    // Union the sets based on the pairs
    for (int i = 0; i < n; ++i) {
        union_sets(uf, pairs[i][0], pairs[i][1]);
    }

    // Print the equivalence classes
    print_equivalence_classes(uf, output);

    fclose(output);

    // Free the Union-Find structure
    free_union_find(uf);

    return 0;
}
