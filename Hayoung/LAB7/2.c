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

void result(FILE* outfile, listPointer first) {
	while (first != NULL) {
		fprintf(outfile, "%d ", first->data);
		first = first->link;
	}
}

void connect(listPointer* chain1, listPointer chain2) {
	if (*chain1 == NULL) {
		*chain1 = chain2;
	}
	else {
		listPointer temp = *chain1;
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = chain2;
	}
}

int main(int argc, char* argv[]) {
	FILE* infile, * outfile;
	infile = fopen(argv[1], "r");
	outfile = fopen(argv[2], "w");

	listPointer chain1 = NULL;
	listPointer chain2 = NULL;
	listPointer x = NULL;

	int value;
	while (fscanf(infile, "%d", &value) != EOF) {
		if (chain1 == NULL) {
			chain1 = create(value);
			x = chain1;
		}
		else {
			x->link = create(value);
			x = x->link;
		}
		if (fgetc(infile) == '\n')
			break;
	}

	while (fscanf(infile, "%d", &value) != EOF) {
		if (chain2 == NULL) {
			chain2 = create(value);
			x = chain2;
		}
		else {
			x->link = create(value);
			x = x->link;
		}
	}

	connect(&chain1, chain2);
	result(outfile, chain1);

	fclose(infile);
	fclose(outfile);

	return 0;
}
