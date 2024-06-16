#include <stdio.h>
#include <stdlib.h>


#define MAX_STACK_SIZE 50
typedef enum{lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;
int stack2[MAX_STACK_SIZE];
char expr[MAX_STACK_SIZE];
char inpr[MAX_STACK_SIZE];

precedence stack[MAX_STACK_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
int top = 0;

precedence get_token(char* symbol, int* n);
precedence get_token2(char* symbol, int* n);
void push(int value);
void push2(int value);
char pop(void);
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
        if (ch != ' ') {
            expr[n++] = ch;
        }
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
        fprintf(outf, "%c ", inpr[a]);
    }

    fprintf(outf, "                //답은 %d", answer);

    fclose(outf);

    return 0;
}

void push(int value) {
    if (top <= 50) {
        stack[++top] = value;
    }
    else {
        printf("Stack is full!\n");
    }
}

void push2(int value)
{
    if (top <= 50) {
        stack2[++top] = value;
    }
    else {
        printf("Stack is full!\n");
    }
}


char pop(void) {
    if (top != -1) {
        int a = stack[top--];
        switch (a)
        {
        case 2: return '+';
        case 3: return '-';
        case 4: return '*';
        case 5: return '/';
        case 6: return '%';
        case 7: return '\0';
        default: return 0;
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
    switch (*symbol)
    {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 3;
    case '*': return 4;
    case '/': return 5;
    case '%': return 6;
    case '\0': return 7;
    default: return 8;
    }
}

precedence get_token2(char* symbol, int* n)
{
    *symbol = inpr[(*n)++];
    switch (*symbol)
    {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 3;
    case '*': return 4;
    case '/': return 5;
    case '%': return 6;
    case '\0': return 7;
    default: return 8;
    }
}

void postfix(void)
{
    char symbol;
    precedence token;
    int n = 0;
    int p = 0;
    stack[0] = 7;
    for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
    {
        if (token == 8)
            inpr[p++] = symbol;
        else if (token == 1)
        {
            while (stack[top] != 0)
                inpr[p++] = pop();
            pop();
        }
        else
        {
            while(isp[stack[top]] >= icp[token])
                inpr[p++] = pop();
            push(token);
        }
    }
    char a = 0;
    while ((a = pop()) != '\0')
        inpr[p++] = a;
}

int eval(void)
{
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    top = -1;
    token = get_token2(&symbol, &n);
    while (token != 7)
    {
        if (token == 8)
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
            case 6: push2(op1 % op2);
            }
        }
        token = get_token2(&symbol, &n);
    }
    return pop2();
}