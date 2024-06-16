#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) {\
		printf("Insufficient memory");\
		exit(1);\
	}\

typedef struct{
    char data;
    int lc;
    int rc;
} node;
FILE* f;
char* c;
int a = 0, top, * stack;
void postorder(node* tree, int ptr) {
    if  (ptr != -1) {
        postorder(tree, tree[ptr].lc);
        postorder(tree, tree[ptr].rc);
        c[a++] = tree[ptr].data;
    }
}
int get_token(char* symbol, int* n) {
    *symbol = c[(*n)++];
    switch (*symbol)
    {
    case '~': return 0;
    case '&': return 1;
    case '|': return 2;
    case '\0': return 3;
    default: return 4;
    }
}
void push(int value) {
    if (top <= 50) {
        stack[++top] = value;
    }
    else {
        printf("Stack is full!\n");
    }
}
int pop(void) {
    if (top != -1) {
        return stack[top--];
    }
    else {
        printf("Stack is empty!\n");
        return 0;
    }
}

int eval(void) {
    char token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;
    token = get_token(&symbol, &n);
    while (token != 3) {
        if (token == 4)
            push(symbol - '0');
        else if (token) {
            op2 = pop();
            op1 = pop();

            switch (token)
            {
            case 1: push(op1 && op2); break;
            case 2: push(op1 || op2);\
            }
        }
        else {
            op1 = pop();
            push(!op1);
        }
        token = get_token(&symbol, &n);
    }
    return pop();
}

int main(int ac, char* av[]) {
    f = fopen(av[1], "r");
    int n, i = 1, j = 0, cntn = 0;
    if (f == NULL) exit(0);
    fscanf(f, "%d", &n);
    node* tree;
    char *v;
    char s[6];
    MALLOC(v, sizeof(char) * n);
    MALLOC(tree, sizeof(tree));
    tree[0].data = 'N';
    tree[0].lc = -1;
    tree[0].rc = -1;
    while (!feof(f)) {
        tree = (node*)realloc(tree, sizeof(node) * (i + 1));
        fscanf(f, "%s ", s);
        if (s[0] == 't') v[j++] = '1';
        else if (s[0] == 'f') v[j++] = '0';
        else if (s[0] == 'o') {
            tree[i].data = '|';
            tree[i].lc = -1;
            tree[i].rc = -1;
            if (i % 2) tree[i / 2].rc = i;
            else tree[i / 2].lc = i;
            i++;
        }
        else if (s[0] == 'n') {
            tree[i].data = '~';
            tree[i].lc = -1;
            tree[i].rc = -1;
            if (i % 2) tree[i / 2].rc = i;
            else tree[i / 2].lc = i;
            i++;
        }
        else if (s[0] == 'a') {
            tree[i].data = '&';
            tree[i].lc = -1;
            tree[i].rc = -1;
            if (i % 2) tree[i / 2].rc = i;
            else tree[i / 2].lc = i;
            i++;
        }
        else if (s[0] == 'e') {
            tree[i].data = 'N';
            tree[i].lc = -1;
            tree[i++].rc = -1;
            cntn++;
        }
        else {
            tree[i].data = v[s[1] - '1'];
            tree[i].lc = -1;
            tree[i].rc = -1;
            if (i % 2) tree[i / 2].rc = i;
            else tree[i / 2].lc = i;
            i++;
        }
    }
    MALLOC(c, sizeof(char) * (i - cntn));
    c[i - cntn - 1] = '\0';
    MALLOC(stack, sizeof(int) * 50);
    postorder(tree, 1);
    if (eval()) printf("True");
    else printf("False");
    free(tree);
    free(c);
    free(stack);
    return 0;
}
