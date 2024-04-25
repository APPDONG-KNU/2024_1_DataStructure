#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s) \
    if (!((p) = malloc(s))) {\
        printf("Insufficient memory");\
        exit(1);\
    }\

typedef struct Node *StackNode;
typedef struct Node {
    int data;
    StackNode link;
} Node;

typedef struct {
    StackNode top;
} LinkedStackType;

void initStack(LinkedStackType *s) {
    s->top = NULL;
}

int isEmpty(LinkedStackType *s) {
    return (s->top == NULL);
}

void push(LinkedStackType *s, int item) {
    StackNode temp = (StackNode)malloc(sizeof(Node));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

int pop(LinkedStackType *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    StackNode temp = s->top;
    int data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void printList(FILE *outf, LinkedStackType *s) {
    StackNode current = s->top;
    while (current != NULL) {
        fprintf(outf, "%-4d ", current->data);
        current = current->link;
    }
    fprintf(outf, "\n");
}

void freeStack(LinkedStackType *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
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
    
    LinkedStackType stack;
    initStack(&stack);

    int num;
    while (fscanf(inf, "%d", &num) == 1) {
        push(&stack, num);
    }
    fclose(inf);

    FILE* outf = fopen(argv[2], "w");
    if (outf == NULL) {
        printf("Error opening output file");
        return 1;
    }

    printList(outf, &stack);

    fclose(outf);

    freeStack(&stack);

    return 0;
}
