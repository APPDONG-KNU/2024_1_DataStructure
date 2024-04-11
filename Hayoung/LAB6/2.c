#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef enum {
    lparen, rparen, and_op, or_op, equal_op, notequal_op, less, greater, lessequal, greaterequal, plus, minus, times, divide, mod, eos, operand
} precedence;

int isp[] = { 0, 16, 16, 15, 15, 14, 14, 14, 14, 12, 12, 13, 13, 13, 12, 0 };
int icp[] = { 17, 16, 16, 15, 15, 14, 14, 14, 14, 12, 12, 13, 13, 13, 12, 0 };

typedef struct {
    int value1;
    int value2;
} returntoken;

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
    case '&':
        if (expr[*n] == '&') {
            (*n)++;
            return and_op;
        }
        else
            return eos;
    case '|':
        if (expr[*n] == '|') {
            (*n)++;
            return or_op;
        }
        else
            return eos;
    case '=': return equal_op;
    case '!':
        if (expr[*n] == '=') {
            (*n)++;
            return notequal_op;
        }
        else
            return eos;
    case '<':
        if (expr[*n] == '=') {
            (*n)++;
            return lessequal;
        }
        else
            return less;
    case '>':
        if (expr[*n] == '=') {
            (*n)++;
            return greaterequal;
        }
        else
            return greater;
    case '\0': return eos;
    default: return operand;
    }
}

char* tokenToSymbol(precedence token) {
    switch (token) {
    case lparen: return "(";
    case rparen: return ")";
    case plus: return "+";
    case minus: return "-";
    case divide: return "/";
    case times: return "*";
    case mod: return "%";
    case and_op: return "&&";
    case or_op: return "||";
    case equal_op: return "==";
    case notequal_op: return "!=";
    case less: return "<";
    case greater: return ">";
    case lessequal: return "<=";
    case greaterequal: return ">=";
    case eos: return "";
    default: return "";
    }
}

void push(int* stack, int* top, int token) {
    stack[++(*top)] = token;
}

char* pop(int* stack, int* top) {
    static char A[MAX_SIZE];
    char* temp = tokenToSymbol(stack[(*top)--]);
    strcpy(A, temp);
    return A;
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
    char A[MAX_SIZE];
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
            while (stack[top] != lparen) {
                strcpy(A, pop(stack, &top));
                for (int i = 0; A[i] != '\0'; ++i)
                    result[result_index++] = A[i];
            }
            pop(stack, &top);
        }
        else {
            while (isp[stack[top]] >= icp[token]) {
                strcpy(A, pop(stack, &top));
                for (int i = 0; A[i] != '\0'; ++i)
                    result[result_index++] = A[i];
            }
            push(stack, &top, token);
        }
    }
    while (stack[top] != eos) {
        strcpy(A, pop(stack, &top));
        for (int i = 0; A[i] != '\0'; ++i)
            result[result_index++] = A[i];
    }
    result[result_index] = '\0';
    removeSpaces(result);
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
            case and_op:
                push(stack, &top, op1 && op2);
                break;
            case or_op:
                push(stack, &top, op1 || op2);
                break;
            case equal_op:
                push(stack, &top, op1 == op2);
                break;
            case notequal_op:
                push(stack, &top, op1 != op2);
                break;
            case less:
                push(stack, &top, op1 < op2);
                break;
            case greater:
                push(stack, &top, op1 > op2);
                break;
            case lessequal:
                push(stack, &top, op1 <= op2);
                break;
            case greaterequal:
                push(stack, &top, op1 >= op2);
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
    printf("¥‰¿∫ %d\n", finalresult);

    return 0;
}