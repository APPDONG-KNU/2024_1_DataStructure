#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, logicaland, logicalor, equality1, equality2, rat1, rat2, rat3, rat4, eos, operand } precedence;
int stack2[MAX_STACK_SIZE];
char expr[MAX_STACK_SIZE];
char inpr[MAX_STACK_SIZE];

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

void initializeStack(Stack* stack) {
    stack->top = NULL;
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

precedence stack[MAX_STACK_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 5, 4, 9, 9, 10, 10, 10, 10, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 5, 4, 9, 9, 10, 10, 10, 10, 0 };
int top = 0;
int p = 0;

precedence get_token(char* symbol, int* n);
precedence get_token2(char* symbol, int* n);
void push(int value);
void push2(int value);
void pop(void);
int pop2(void);
void postfix(void);


int main(int ac, char* av[]) {
    FILE* inf, *outf;
    int n = 0;
    char ch;

    inf = fopen(av[1], "r");
    if (inf == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    while ((ch = fgetc(inf)) != EOF) {
        expr[n++] = ch;
    }

    expr[n] = '\0';

    fclose(inf);

    postfix();

    int answer = eval();

    outf = fopen(av[2], "w");
    if (outf == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    for (int a = 0; inpr[a] != '\0'; a++) {
        fprintf(outf, "%c", inpr[a]);
    }

    fprintf(outf, "                //답은 %d", answer);

    fclose(outf);

    return 0;
}

void push(value) {
    if (top <= 100) {
        stack[++top] = value;
    }
    else {
        printf("Stack is full!\n");
    }
}

void push2(int value)
{
    if (top <= 100) {
        stack2[++top] = value;
    }
    else {
        printf("Stack is full!\n");
    }
}


void pop(void) {
    if (top != -1) {
        int a = stack[top--];
        switch (a)
        {
        case 2: {inpr[p++] = '+'; inpr[p++] = ' '; break; }
        case 3: {inpr[p++] = '-'; inpr[p++] = ' '; break; }
        case 4: {inpr[p++] = '*'; inpr[p++] = ' '; break;}
        case 5: {inpr[p++] = '/'; inpr[p++] = ' '; break; }
        case 6: {inpr[p++] = '%'; inpr[p++] = ' '; break; }
        case 7: 
        {inpr[p++] = '&'; inpr[p++] = '&'; inpr[p++] = ' '; break; }
        case 8: 
        {inpr[p++] = '|'; inpr[p++] = '|'; inpr[p++] = ' '; break; }
        case 9: 
        {inpr[p++] = '='; inpr[p++] = '=';  inpr[p++] = ' '; break; }
        case 10: {inpr[p++] = '!'; inpr[p++] = '='; inpr[p++] = ' '; break; }
        case 11: {inpr[p++] = '<'; inpr[p++] = ' '; break; }
        case 12: {inpr[p++] = '>'; inpr[p++] = ' '; break; }
        case 13: {inpr[p++] = '<'; inpr[p++] = '=';  inpr[p++] = ' '; break; }
        case 14: { inpr[p++] = '>'; inpr[p++] = '='; inpr[p++] = ' '; break; }
        case 15: inpr[p++] = '\0';
        }
    }
    else {
        printf("Stack is empty!\n");
        return '\0';
    }
}

int pop2(void)
{
    if (top != -1) {
        return stack2[top--];
    }
    else {
        printf("Stack is empty!\n");
        return 0;
    }
}

precedence get_token(char* symbol, int* n)
{
    *symbol = expr[(*n)++];
    char symbol2 = expr[(*n)++];
    if (symbol2 == ' ' || symbol2 == '\0')
    {
        switch (*symbol)
        {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
        case '%': return 6;
        case '<': return 11;
        case '>': return 12;
        case '\0': return 15;
        default: return 16;
        }
    }
    else
    {
        (*n)++;
        switch (*symbol)
        {
        case '&': return 7;
        case '|': return 8;
        case '=': return 9;
        case '!': return 10;
        case '<': return 13;
        case '>': return 14;
        case '\0': return 15;
        }
    }
}

precedence get_token2(char* symbol, int* n)
{
    *symbol = inpr[(*n)++];
    char symbol2 = inpr[(*n)++];
    if (symbol2 == ' ' || symbol2 == '\0')
    {
        switch (*symbol)
        {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
        case '%': return 6;
        case '<': return 11;
        case '>': return 12;
        case '\0': return 15;
        default: return 16;
        }
    }
    else
    {
        (*n)++;
        switch (*symbol)
        {
        case '&': return 7;
        case '|': return 8;
        case '=': return 9;
        case '!': return 10;
        case '<': return 13;
        case '>': return 14;
        case '\0': return 15;
        }
    }
}

void postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    stack[0] = 15;
    for (token = get_token(&symbol, &n); token != 15; token = get_token(&symbol, &n))
    {
        if (token == 16)
        {
            inpr[p++] = symbol;
            inpr[p++] = ' ';
        }
        else if (token == 1)
        {
            while (stack[top] != 0)
                pop();
            pop();
        }
        else
        {
            while (isp[stack[top]] >= icp[token])
                pop();
            push(token);
        }
    }
    int a = 0;
    while (a = stack[top] != 15)
    {
        pop();
    }
}

int eval(void)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;
    token = get_token2(&symbol, &n);
    while (token != 15)
    {
        if (token == 16)
            push2(symbol - '0');
        else
        {
            op2 = pop2();
            op1 = pop2();

            switch (token)
            {
            case 2: push2(op1 + op2); break;
            case 3: push2(op1 - op2); break;
            case 4: push2(op1 * op2); break;
            case 5: push2(op1 / op2); break;
            case 6: push2(op1 % op2); break;
            case 7: push2(op1 && op2); break;
            case 8: push2(op1 || op2); break;
            case 9: push2(op1 == op2); break;
            case 10: push2(op1 != op2); break;
            case 11: push2(op1 < op2); break;
            case 12: push2(op1 > op2); break;
            case 13: push2(op1 <= op2); break;
            case 14: push2(op1 >= op2); 

            }
        }
        token = get_token2(&symbol, &n);
    }
    return pop2();
}