#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef enum {
    lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

precedence getToken(char* symbol, char* expr, int* n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '\0': return eos;
    default: return operand;
    }
}

char tokenToSymbol(precedence token) {
    switch (token) {
    case lparen: return '(';
    case rparen: return ')';
    case plus: return '+';
    case minus: return '-';
    case divide: return '/';
    case times: return '*';
    case mod: return '%';
    case eos: return '\0';
    default: return 0;
    }
}

void push(int* stack, int* top, int token) {
    stack[++(*top)] = token;
}

char pop(int* stack, int* top) {
    return tokenToSymbol(stack[(*top)--]);
}

int pop2(int* stack, int* top) {
    return stack[(*top)--];
}

void removeSpaces(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i])) {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

void postfix(char* expr, char* result) {
    char symbol;
    precedence token;
    int n = 0;
    int top = 0;
    int result_index = 0;
    int stack[MAX_SIZE] = { 0 };
    stack[0] = eos;

    for (token = getToken(&symbol, expr, &n); token != eos; token = getToken(&symbol, expr, &n)) {
        if (token == operand)
            result[result_index++] = symbol;

        else if (token == lparen)
            push(stack, &top, token);

        else if (token == rparen) {
            while (stack[top] != lparen)
                result[result_index++] = pop(stack, &top);
            pop(stack, &top);
        }
        else {
            while (isp[stack[top]] >= icp[token])
                result[result_index++] = pop(stack, &top);
            push(stack, &top, token);
        }
    }
    while (token = getToken(&symbol, expr, &n) != eos)
        result[result_index++] = pop(stack, &top);
    result[result_index] = '\0';
    return removeSpaces(result);
}

int evaluatePostfix(char* expr) {

    removeSpaces(expr);

    char symbol;
    precedence token;
    int n = 0;
    int op1, op2;
    int stack[MAX_SIZE] = { 0 };
    int top = -1;

    while ((token = getToken(&symbol, expr, &n)) != eos) {
        if (token == operand) {
            push(stack, &top, symbol - '0');
        }
        else {
            op2 = pop2(stack, &top);
            op1 = pop2(stack, &top);
            switch (token) {
            case plus:
                push(stack, &top, op1 + op2);
                break;
            case minus:
                push(stack, &top, op1 - op2);
                break;
            case times:
                push(stack, &top, op1 * op2);
                break;
            case divide:
                push(stack, &top, op1 / op2);
                break;
            case mod:
                push(stack, &top, op1 % op2);
                break;
            }
        }
    }
    int finalresult = pop2(stack, &top);
    return finalresult;
}


int main(int argc, char* argv[]) {
    FILE* infile;
    char expr[MAX_SIZE];
    char result[1000];
    int finalresult;

    infile = fopen(argv[1], "r");

    fgets(expr, MAX_SIZE, infile);
    fclose(infile);

    postfix(expr, result);
    printf("%s\n", result);

    finalresult = evaluatePostfix(result);
    printf("¥‰¿∫ : %d\n", finalresult);

    return 0;
}
