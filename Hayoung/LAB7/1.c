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

void insert(listPointer* first, listPointer x, int data) {
	listPointer temp;
	temp = create(data);
	if (*first) {
		temp->link = x->link;
		x->link = temp;
	}
	else {
		temp->link = *first;
		*first = temp;
	}
}

void delete(listPointer* first, listPointer trail, listPointer x) {
	if (trail)
		trail->link = x->link;
	else
		*first = (*first)->link;

	if (x == *first)
		*first - (*first)->link;

	free(x);
}

int length(listPointer first) {
	int len = 0;
	while (first != NULL) {
		len++;
		first = first->link;
	}
	return len;
}

void result(listPointer first) {
	printf("result: ");
	while (first != NULL) {
		printf("%d ", first->data);
		first = first->link;
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	FILE* infile;
	listPointer first = NULL;
	listPointer x = NULL;
	listPointer trail = NULL;

	int menu, position, data;

	infile = fopen(argv[1], "r");

	int value;
	while (fscanf(infile, "%d", &value) != EOF) {
		if (first == NULL) {
			first = create(value);
		}
		else {
			x = first;
			while (x->link != NULL) {
				x = x->link;
			}
			x->link = create(value);
		}
	}

	fclose(infile);

	result(first);

	printf("+----------------+\n");
	printf(" 1. insert\n");
	printf(" 2. delete\n");
	printf(" 3. length\n");
	printf(" 4. exit\n");
	printf("+----------------+\n");

	while (1) {
		printf("Menu: ");
		scanf("%d", &menu);
		switch (menu) {
		case 1:
			printf("insert: ");
			scanf("%d %d", &position, &data);
			if (position == 0)
			{
				listPointer temp;
				temp = create(data);
				temp->link = first;
				first = temp;
			}
			else
			{
				x = first;
				for (int i = 0; i < position - 1; i++)
					x = x->link;
				insert(&first, x, data);
			}

			result(first);
			printf("\n");
			break;
		case 2:
			printf("delete: ");
			scanf("%d", &position);
			x = first;
			for (int i = 0; i < position - 1; i++) {
				trail = x;
				x = x->link;
			}
			delete(&first, trail, x);
			result(first);
			printf("\n");
			break;
		case 3:
			printf("length: %d\n", length(first));
			printf("\n");
			break;
		case 4:
			printf("exit\n");
			exit(0);
		default:
			printf("wrong number.\n");
			printf("\n");
			break;
		}
	}

	return 0;
}
