#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    int accountNum;
    char name[30];
    int deposit;
    int loan;
};

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;

    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Error\n");
        return 1;
    }

    struct account* accounts = (struct account*)malloc(sizeof(struct account) * 100);
    if (accounts == NULL) {
        fprintf(stderr, "Fail\n");
        fclose(infile);
        return 1;
    }

    int n = 0;
    while (fscanf(infile, "%d %s %d %d", &accounts[n].accountNum, accounts[n].name, &accounts[n].deposit, &accounts[n].loan) == 4) {
        n++;
    }

    fclose(infile);

    int max = accounts[0].loan;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (accounts[i].loan > max) {
            max = accounts[i].loan;
            index = i;
        }
    }

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error\n");
        free(accounts);
        return 1;
    }

    if (index != -1)
        fprintf(outfile, "%d %s %d %d\n", accounts[index].accountNum, accounts[index].name, accounts[index].deposit, accounts[index].loan);

    fclose(outfile);

    free(accounts);

    return 0;
}
