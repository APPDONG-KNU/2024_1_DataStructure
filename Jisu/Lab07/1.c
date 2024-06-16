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

void printList(listPointer chain) {
	listPointer first = chain;
	for (; first; first = first->link) printf("%-4d ", first->data);
	printf("\n");
}

listPointer createNode(int data) {
    listPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->link = NULL;
    cnt++;
    return newNode;
}

listPointer readNums(char* av) {
    FILE* inf = fopen(av, "r");
    if (inf == NULL) {
		printf("error1");
		exit(1);
	}

    listPointer head = NULL;
    listPointer tail = NULL;
    int n;

    while (fscanf(inf, "%d", &n) != EOF) {
        listPointer newNode = createNode(n);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->link = newNode;
            tail = newNode;
        }
    }

    fclose(inf);
    return head;
}

void insert(listPointer *first, int n, int d) {
    listPointer temp, x = *first;
    MALLOC(temp, sizeof(*temp));
    temp->data = d;
    temp->link = NULL;

    if (n == 0) {
        temp->link = *first;
        *first = temp;
    }
    else {
        for (int i = 1; i < n && x != NULL; i++) {
            x = x->link;
        }
        if (x == NULL) {
            printf("Error: Index out of range\n");
            free(temp);
            return;
        }
        temp->link = x->link;
        x->link = temp;
    }
    cnt++;
}


void delete(listPointer *first, int n) {
    listPointer trail = NULL, x = *first;
    if (n == 0) {
        *first = (*first)->link;
        free(x);
        return;
    }
    else {
        for (int i = 0; i < n && x != NULL; i++) {
            trail = x;
            x = x->link;
        }
        if (x == NULL) {
            printf("Error: Index out of range\n");
            return;
        }
        trail->link = x->link;
    }
    free(x);
    cnt--;
}


void ask(int menu, listPointer* l) {
    int n, d;
    printf("\nMenu: ");
    scanf("%d", &menu);
    if (menu < 1 || menu > 4) ask(menu, l);
    else {
        switch (menu)
        {
        case 1: printf("insert: "); scanf("%d %d", &n, &d); insert(l, n, d);
            printf("result: "); printList(*l);
            break;
        case 2: printf("delete: "); scanf("%d", &n); delete(l, n);
            printf("result: "); printList(*l);
            break;
        case 3: printf("length: "); printf("%d\n", cnt);
            break;
        case 4: printf("exit\n"); exit(0);
            break;
        default:
            break;
        }
    }
}

int main(int ac, char* av[]) {
    int menu;
	listPointer chain = readNums(av[1]);
	
    printf("chain: ");
	printList(chain);
	printf("+----------------+\n");
	printf("    1. insert\n");
	printf("    2. delete\n");
	printf("    3. length\n");
	printf("    4. exit\n");
	printf("+----------------+\n");

    while(1) {
        ask(menu, &chain);
    }
	free(chain);

	return 0;
}
