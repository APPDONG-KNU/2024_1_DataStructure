#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 20

typedef struct {
    short int vert;
    short int horiz;
} offsets;

typedef struct {
    short int row;
    short int col;
    short int dir;
} element;

element stack[MAX_SIZE * MAX_SIZE];
int top = -1;

void push(element item) {
    stack[++top] = item;
}

element pop() {
    return stack[top--];
}

int main(int argc, char* argv[]) {
    FILE* infile, * outfile;
    int numCol, numRow;
    int found = 0;
    int row, col, dir, nextRow, nextCol;

    int maze[MAX_SIZE][MAX_SIZE];
    int mark[MAX_SIZE][MAX_SIZE];

    offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");

    fscanf(infile, "%d %d", &numRow, &numCol);

    for (int i = 0; i < numRow; i++)
    {
        for (int j = 0; j < numCol; j++)
        {
            fscanf(infile, "%d", &maze[i][j]);
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            mark[i][j] = 0;
        }
    }

    mark[0][0] = 1;
    top = 0;
    stack[0].row = 0;
    stack[0].col = 0;
    stack[0].dir = 0;

    while (top > -1 && found == 0)
    {
        element position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;

        while (dir < 8 && found == 0)
        {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextCol == numCol && nextRow == numRow)
            {
                found = 1;
                element nextPos;
                nextPos.row = row;
                nextPos.col = col;
                nextPos.dir = ++dir;
                push(nextPos);
            }
            else if (nextRow < numRow && nextCol < numCol && maze[nextRow][nextCol] == 0 && mark[nextRow][nextCol] == 0)
            {
                mark[nextRow][nextCol] = 1;
                element nextPos;
                nextPos.row = row;
                nextPos.col = col;
                nextPos.dir = ++dir;
                push(nextPos);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
            {
                ++dir;
            }
        }
    }

    if (found) {
        fprintf(outfile, "success\n");

        fprintf(outfile, "\npath는 ");
        for (int i = 0; i < top + 1; i++)
            fprintf(outfile, "(%d,%d) ", stack[i].row + 1, stack[i].col + 1);
        fprintf(outfile, "\n");
        fprintf(outfile, "\n사용한 스택의 크기 / 스택의 최대 크기 = %d / %d\n", top + 1, numCol * numRow);
    }
    else
    {
        fprintf(outfile, "fail\n");
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
