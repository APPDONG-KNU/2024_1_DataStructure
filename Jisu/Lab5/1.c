#include <stdio.h>

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
    if(*top < 0)
        printf("Stack is Empty.\n");
    else
        result = stack[(*top)--];
    return result;
}

void push(int *top, element position, element* stack) {
    stack[++*top] = position;
}

void path (FILE* f, int m_r, int m_c, int maze[20][20]) {
    int i, row, col, nextRow, nextCol, dir, found = 0, top = 0, mark[22][22] = { 0 };
    element stack[m_r * m_c], position;
    offsets move[8] = {{1, 1}, {1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    mark[1][1] = 1;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 0;
    while (top > -1 && found == 0) {
        position = pop(&top, stack);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir < 8 && found == 0) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            
            if (nextRow == m_r + 1 && nextCol == m_c + 1) {
                found = 1;
                position.row++;
                push(&top, position, stack);
            }
            else if (maze[nextRow - 1][nextCol - 1] == 0 && mark[nextRow][nextCol] == 0) {
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
        fprintf(f, "success\n\n");
        fprintf(f, "path는");
        for (i = 0; i <= top; i++) {
            fprintf(f, " (%d, %d)", stack[i].row, stack[i].col);
        }
        fprintf(f, "\n\n사용한 스택의 크기 / 스택의 최대 크기 = %d / %d", top + 1, m_r * m_c);
    }
    else fprintf(f, "fail\n");
}

int main(int ac, char* av[]) {
    FILE* inf, *outf;
    element position;
    int i, r, c, n_r, n_c, m_r, m_c, dir;
    int found = 0;
    int maze[20][20];
    if ((inf = fopen(av[1], "r")) == NULL) {
        printf("error1");
        return 1;
    }
    fscanf(inf, "%d %d ", &m_r, &m_c);
    for (i = 0; i < m_r; i++) {
        for (int j = 0; j < m_c; j++)
            fscanf(inf, "%d", &maze[i][j]);
    }
    fclose(inf);

    if ((outf = fopen(av[2], "w")) == NULL) {
        printf("error2");
        return 1;
    }
    
    path(outf, m_r, m_c, maze);

    fclose(outf);

    return 0;
}
