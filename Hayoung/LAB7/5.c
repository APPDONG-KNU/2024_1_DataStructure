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

typedef struct {
    int key;
} element;

typedef struct stack* stackPointer;
typedef struct stack {
    element data;
    stackPointer link;
} stack;

stackPointer top = NULL;

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

void push(int token) {
    stackPointer temp = (stackPointer)malloc(sizeof(stack));
    temp->data.key = token;
    temp->link = top;
    top = temp;
}

char* pop() {
    stackPointer temp = top;
    top = top->link;
    char* symbol = tokenToSymbol(temp->data.key);
    free(temp);
    return symbol;
}

int pop2() {
    int token = top->data.key;
    stackPointer temp = top;
    top = top->link;
    free(temp);
    return token;
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
    int result_index = 0;
    push(eos);

    for (token = getToken(&symbol, expr, &n); token != eos; token = getToken(&symbol, expr, &n)) {
        if (token == operand)
            result[result_index++] = symbol;
        else if (token == lparen)
            push(token);
        else if (token == rparen) {
            while (top->data.key != lparen) {
                char* A = pop();
                for (int i = 0; A[i] != '\0'; ++i)
                    result[result_index++] = A[i];
            }
            pop();
        }
        else {
            while (isp[top->data.key] >= icp[token]) {
                char* A = pop();
                for (int i = 0; A[i] != '\0'; ++i)
                    result[result_index++] = A[i];
            }
            push(token);
        }
    }
    while (top->data.key != eos) {
        char* A = pop();
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
    while ((token = getToken(&symbol, expr, &n)) != eos) {
        if (token == operand) {
            push(symbol - '0');
        }
        else {
            op2 = pop2();
            op1 = pop2();
            switch (token) {
            case plus:
                push(op1 + op2);
                break;
            case minus:
                push(op1 - op2);
                break;
            case times:
                push(op1 * op2);
                break;
            case divide:
                push(op1 / op2);
                break;
            case mod:
                push(op1 % op2);
                break;
            case and_op:
                push(op1 && op2);
                break;
            case or_op:
                push(op1 || op2);
                break;
            case equal_op:
                push(op1 == op2);
                break;
            case notequal_op:
                push(op1 != op2);
                break;
            case less:
                push(op1 < op2);
                break;
            case greater:
                push(op1 > op2);
                break;
            case lessequal:
                push(op1 <= op2);
                break;
            case greaterequal:
                push(op1 >= op2);
                break;
            }
        }
    }
    int finalresult = pop2();
    return finalresult;
}

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    char expr[MAX_SIZE];
    char result[1000];
    int finalresult;

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    fgets(expr, MAX_SIZE, infile);
    fclose(infile);

    postfix(expr, result);
    fprintf(outfile, "%s\n", result);

    finalresult = evaluatePostfix(result);
    fprintf(outfile, "¥‰¿∫ %d\n", finalresult);

    return 0;
}
