#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct listN *listPointer;
typedef struct listN {
    int data;
    listPointer link;
};

int cnt = 0;

void printList(listPointer chain, char* av) {
    FILE* outf = fopen(av, "w");
    if (outf == NULL) {
        printf("error1");
        exit(1);
    }
    listPointer first = chain;
    for (; first; first = first->link) fprintf(outf, "%-4d ", first->data);
    fprintf(outf, "\n");
    fclose(outf);
}

listPointer createNode(int data) {
    listPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->link = NULL;
    cnt++;
    return newNode;
}

listPointer readNums(FILE* inf, listPointer* tail) {
    listPointer head = NULL;
    int n, k;

    while ((k = fgetc(inf)) != '\n' && k != EOF) {
        ungetc(k, inf);
        k = fscanf(inf, "%d", &n);
        if (k != 1) {
            break;
        }
        listPointer newNode = createNode(n);
        if (head == NULL) {
            head = newNode;
            *tail = newNode;
        } else {
            (*tail)->link = newNode;
            *tail = newNode;
        }
    }
    return head;
}

void freeList(listPointer chain) {
    listPointer temp;
    while (chain != NULL) {
        temp = chain;
        chain = chain->link;
        free(temp);
    }
}

int main(int ac, char* av[]) {
    int menu;
    listPointer tail1, tail2;
    char c;
    
    FILE* inf = fopen(av[1], "r");
    if (inf == NULL) {
        printf("error1");
        exit(1);
    }
    
    listPointer chain1 = readNums(inf, &tail1);
    
    fseek(inf, 0, SEEK_SET);
    
    while ((c = fgetc(inf)) != '\n' && c != EOF);
    
    listPointer chain2 = readNums(inf, &tail2);
    if (chain2 == NULL) {
        fclose(inf);
        inf = fopen(av[1], "r");
        if (inf == NULL) {
            printf("error1");
            exit(1);
        }
        while ((c = fgetc(inf)) != '\n' && c != EOF);
        chain2 = readNums(inf, &tail2);
    }
    
    fclose(inf);
    
    tail1->link = chain2;
    printList(chain1, av[2]);

    freeList(chain1);
    freeList(chain2);

    return 0;
}