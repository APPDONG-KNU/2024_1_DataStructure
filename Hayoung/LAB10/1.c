#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main(int argc, char* argv[]) {
    FILE* infile;
    int tree[15];

    infile = fopen(argv[1], "r");

    int num;
    fscanf(infile, "%d", &num);

    int index = 0, data;

    while(!feof(infile)) {
        fscanf(infile, "%d", &tree[index]);
        printf("%d ", tree[index]);
        index++;
    }

    fclose(infile);
 }
        
