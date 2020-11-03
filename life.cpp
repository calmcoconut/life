#include <time.h>
#include <stdlib.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#define SLEEP Sleep(300)
#define CLS system("cls")
#else
#include <unistd.h>
#define SLEEP usleep(3000)
#define CLS printf("\033[H\033[J")
#endif

#define ROWS 3
#define COLS 3

using namespace std;

int xWrap(const int x);
int yWrap(const int y);
int countNeighbors(int board[][ROWS], int currentX, int currentY);

// isRand=0 for dead state
void initBoard(int board[][ROWS], bool isRand)
{
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (isRand)
            {
                board[i][j] = rand() % 2;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void nextBoardState(int board[][ROWS])
{
    int nextBoard[COLS][ROWS];
    initBoard(nextBoard, 0);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int neighbors = countNeighbors(board, j, i);
            // 0-1 becomes dead due to underpop
            if (neighbors == 0 && board[i][j] == 1)
                nextBoard[i][j] = 1;
            // 2-3 stays alive, e.g. stays the same
            // 3+ dies of overpop
            if (neighbors > 3)
                nextBoard[i][j] = 0;
            // any dead cell with exactly 3 neighbors becomes alive.
            if (neighbors == 3 && board[i][j] == 1)
                nextBoard[i][j] = 1;
        }
    }
}

// will wrap around
int countNeighbors(int board[][ROWS], int currentX, int currentY)
{
    /*
        col-1, row-1 | row-1 | col+1, row-1
        col-1        |  cell | col+1
        col-1, row+1 | row+1 | col+1, row+1
    */
    int count = 0;
    // check row above.
    if (board[currentX][yWrap(currentY-1)])
        count++;
    if (board[xWrap(currentX-1)][yWrap(currentY-1)])
        count++;
    if (board[xWrap(currentX+1)][yWrap(currentY-1)])
        count++;
    // check immediate col
    if (board[xWrap(currentX-1)][currentY])
        count++;
    if (board[xWrap(currentX+1)][currentY])
        count++;
    // check row below
    if (board[currentX][yWrap(currentY+1)])
        count++;
    if (board[xWrap(currentX-1)][yWrap(currentY+1)])
        count++;
    if (board[xWrap(currentX+1)][yWrap(currentY+1)])
        count++;
    return count;
}

// returns the wrapped value of x
int xWrap(const int x)
{
    if (x >= COLS)
        return 0;
    if (x == -1)
        return COLS -1;
    return x;
}

// returns the wrapped value of y
int yWrap(const int y)
{
    if (y >= ROWS)
    {
        return 0;
    }
    if (y == -1)
    {
        return ROWS-1;
    }
    return y;
}

void printBoard(int board[][ROWS])
{
    for (int i = 0; i < COLS + 14; i++)
    {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i < COLS; i++)
    {
        cout << "|\t";
        for (int j = 0; j < ROWS; j++)
        {
            if (board[j][i])
            {
                cout << "#";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "\t|\n";
    }
    for (int i = 0; i < COLS + 14; i++)
    {
        cout << "-";
    }
    cout << "\n\n";
}