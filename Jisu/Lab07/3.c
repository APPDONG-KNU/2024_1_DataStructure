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
} listN;

int cnt = 0;

void printList(listPointer chain, char* av) {
    FILE* outf = fopen(av, "w");
    if (outf == NULL) {
        printf("Error opening output file");
        exit(1);
    }
    listPointer current = chain;
    while (current != NULL) {
        fprintf(outf, "%-4d ", current->data);
        current = current->link;
    }
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

listPointer readNums(FILE* inf) {
    listPointer head = NULL;
    listPointer tail = NULL;
    int n;

    while (fscanf(inf, "%d", &n) == 1) {
        listPointer newNode = createNode(n);
        if (head == NULL) {
            head = newNode;
        } else {
            tail->link = newNode;
        }
        tail = newNode;
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

listPointer reverseList(listPointer head) {
    listPointer prev = NULL;
    listPointer current = head;
    listPointer next = NULL;
    while (current != NULL) {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }
    return prev;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE* inf = fopen(argv[1], "r");
    if (inf == NULL) {
        printf("Error opening input file");
        return 1;
    }
    
    listPointer chain = readNums(inf);
    fclose(inf);

    listPointer reversedChain = reverseList(chain);

    printList(reversedChain, argv[2]);

    freeList(reversedChain);

    return 0;
}
