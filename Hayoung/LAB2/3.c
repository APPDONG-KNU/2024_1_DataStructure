#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;

    infile = fopen(argv[1], "r");

    char** data = (char**)malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; ++i) 
        data[i] = (char*)malloc(100 * sizeof(char));

    fgets(data[0], 100, infile);
    data[0][strcspn(data[0], "\n")] = '\0';

    fgets(data[1], 100, infile);
    data[1][strcspn(data[1], "\n")] = '\0';

    fclose(infile);

    outfile = fopen(argv[2], "w");
 
    fprintf(outfile, "%s\n%s", data[0], data[1]);

    fclose(outfile);

    return 0;
}
