#include <stdio.h>
#include <stdlib.h>

#define SIDE 8
#define VISITED 1
#define NOT_VISITED 0

#define GOAL_X 7
#define GOAL_Y 7

#define FALSE 0
#define TRUE !FALSE

void printBoard(int board[][SIDE]);
int goHorsie(int board[][SIDE], int x, int y, int step, int corners[4]);

int main(void)
{
    int board[SIDE][SIDE] = { NOT_VISITED };
    int corners[4] = { FALSE, FALSE, FALSE, FALSE }; // corners[0]: (0,0), corners[1]: (0,7), corners[2]: (7,0), corners[3]: (7,7)
    if (goHorsie(board, 0, 0, 1, corners))
    {
        printf("Yes, There is a path visiting all corners! Here it is:\n");
        printBoard(board);
    }
    else
    {
        printf("No path visiting all corners...");
    }
    getchar();
    return 0;
}

/*
Function checks if knight can travel from top left corner and visit all corners
input: the board, current step, and corners array to track corners visited
output: whether a path was found
*/
int goHorsie(int board[][SIDE], int x, int y, int step, int corners[4])
{
    int res = FALSE;
    int prev_corners[4];

    // Save current state of corners
    for (int i = 0; i < 4; i++) {
        prev_corners[i] = corners[i];
    }

    // Update corners visited
    if (x == 0 && y == 0) corners[0] = TRUE;
    if (x == 0 && y == 7) corners[1] = TRUE;
    if (x == 7 && y == 0) corners[2] = TRUE;
    if (x == 7 && y == 7) corners[3] = TRUE;

    // Check if all corners are visited and we reached the goal
    if (corners[0] && corners[1] && corners[2] && corners[3])
    {
        board[x][y] = step;
        res = TRUE;
    }
    else if (x >= SIDE || y >= SIDE || x < 0 || y < 0 || // out of the board
        board[x][y] != NOT_VISITED) // we were here already!
    {
        res = FALSE;
    }
    else
    {
        board[x][y] = step;
        step++;
        // changing order here will change the path, because once a condition is verified (TRUE) the rest aren't checked
        res = goHorsie(board, x + 2, y + 1, step, corners) ||
            goHorsie(board, x + 2, y - 1, step, corners) ||
            goHorsie(board, x + 1, y + 2, step, corners) ||
            goHorsie(board, x + 1, y - 2, step, corners) ||
            goHorsie(board, x - 2, y + 1, step, corners) ||
            goHorsie(board, x - 2, y - 1, step, corners) ||
            goHorsie(board, x - 1, y + 2, step, corners) ||
            goHorsie(board, x - 1, y - 2, step, corners);
        if (!res)
        {
            board[x][y] = NOT_VISITED;
            // Restore previous state of corners if backtracking
            for (int i = 0; i < 4; i++) {
                corners[i] = prev_corners[i];
            }
        }
    }

    return res;
}

/*
Function prints the board
input: board to print
output: none
*/
void printBoard(int board[][SIDE])
{
    int i = 0, j = 0;
    for (i = 0; i < SIDE; i++)
    {
        for (j = 0; j < SIDE; j++)
        {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}
