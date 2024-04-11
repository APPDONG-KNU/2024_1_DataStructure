#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer create(int data) {
    listPointer temp = (listPointer)malloc(sizeof(listNode));
    temp->data = data;
    temp->link = NULL;
    return temp;
}

listPointer* reverseLinkedList(listPointer* head) {
    listPointer prev = NULL;
    listPointer current = head;
    listPointer next = NULL;

    while (current != NULL) {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

void result(FILE* outfile, listPointer first) {
    while (first != NULL) {
        fprintf(outfile, "%d ", first->data);
        first = first->link;
    }
}

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    listPointer first = NULL;
    listPointer x = NULL;

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    int value;
    while (fscanf(infile, "%d", &value) != EOF) {
        if (first == NULL) {
            first = create(value);
            x = first;
        }
        else {
            x->link = create(value);
            x = x->link;
        }
    }

    first = reverseLinkedList(first);

    result(outfile, first);

    fclose(infile);
    fclose(outfile);

    return 0;
}
