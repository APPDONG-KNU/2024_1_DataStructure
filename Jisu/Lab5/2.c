#include <stdio.h>
#include <stdlib.h>

typedef struct {
    short int vert;
    short int horiz;
} offsets;

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;

element pop(int* top, element* stack) {
    element result;
    if(*top<0){
        printf("Stack is Empty.\n");
    }
    else{
        result = stack[*top];
        (*top)--;
    }
    return result;
}

void push(int *top, element position, element* stack) {
    (*top)++;
    element* newStack = (element*)malloc((*top + 1) * sizeof(element));
    if (newStack == NULL) exit(1);
    *stack = *newStack;
    stack[*top].row = position.row;
    stack[*top].col = position.col;
    stack[*top].dir = position.dir;
}

void path (FILE* f, int mark[20][20], int top, element* stack, offsets* move, int m_r, int m_c, int maze[20][20]) {
    int i, row, col, nextRow, nextCol, dir;
    int found = 0;
    element position;

    top = 0;
    mark[0][0] = 1;
    stack[0].row = 0;
    stack[0].col = 0;
    stack[0].dir = 0;
    while (top > -1 && found == 0) {
        position = pop(&top, stack);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir < 8 && found == 0) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            
            if (nextRow == m_r && nextCol == m_c) {
                found = 1;
                position.row++;
                push(&top, position, stack);
            }
            else if (maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] == 0) {
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(&top, position, stack);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else ++dir;
        }
    }

    if (found) {
        stack[0].row = 0;
        stack[0].col = 0;
        fprintf(f, "success\n\n");
        fprintf(f, "path는");
        for ( i = 0; i <= top; i++ ) {
            fprintf(f, " (%d, %d)", stack[i].row + 1, stack[i].col + 1);
        }
        fprintf(f, "\n\n사용한 스택의 크기 / 스택의 최대 크기 = %d / %d", top + 1, m_r * m_c);
    }
    else fprintf(f, "fail\n");
}

int main(int ac, char* av[]) {
    FILE* inf, *outf;
    element position;
    offsets move[8] = {{1, 1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
    int i, r, c, n_r, n_c, m_r, m_c, dir, top = 0;
    int found = 0;
    int maze[20][20];
    inf = fopen(av[1], "r");
    if (inf == NULL) {
        printf("error1");
        return 1;
    }
    fscanf(inf, "%d %d ", &m_r, &m_c);
    element* stack = (element*)malloc(sizeof(element));
    if (stack == NULL) exit(1);
    int mark[20][20] = { 0 };
    for (i = 0; i < m_r; i++) {
        for (int j = 0; j < m_c; j++)
            fscanf(inf, "%d", &maze[i][j]);
    }
    fclose(inf);

    outf = fopen(av[2], "w");
    if (outf == NULL) {
        printf("error2");
        return 1;
    }
    
    path(outf, mark, top, stack, move, m_r, m_c, maze);

    fclose(outf);

    return 0;
}
