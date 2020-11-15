#include <time.h>
#include <stdlib.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#define SLEEP Sleep(300)
#define CLS system("cls")
#else
#include <unistd.h>
#define SLEEP usleep(450000)
#define CLS printf("\033[H\033[J")
#endif

#define ROWS 26
#define COLS 26

using namespace std;

int rowWrap(const int x);
int colWrap(const int y);
int countNeighbors(int board[][ROWS], int row, int col);

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
            int neighbors = countNeighbors(board, i, j);
            // 0-1 becomes dead due to underpop
            if (neighbors <= 1 && board[i][j] == 1)
                nextBoard[i][j] = 0;
            // 2-3 stays alive, e.g. stays the same
            // 3+ dies of overpop
            else if (neighbors > 3)
                nextBoard[i][j] = 0;
            // any dead cell with exactly 3 neighbors becomes alive.
            else if (neighbors == 3 && board[i][j] == 0)
                nextBoard[i][j] = 1;
            else
                nextBoard[i][j] = board[i][j];
        }
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = nextBoard[i][j];
        }
    }
}

// will wrap around
int countNeighbors(int board[][ROWS], int row, int col)
{
    /*
        col-1, row-1 | row-1 | col+1, row-1
        col-1        |  cell | col+1
        col-1, row+1 | row+1 | col+1, row+1
    */
    int count = 0;
    // check row above.
    if (board[rowWrap(row-1)][colWrap(col)])
        count++;
    if (board[rowWrap(row-1)][colWrap(col-1)])
        count++;
    if (board[rowWrap(row-1)][colWrap(col+1)])
        count++;
    // check immediate col
    if (board[rowWrap(row)][colWrap(col-1)])
        count++;
    if (board[rowWrap(row)][colWrap(col+1)])
        count++;
    // check row below
    if (board[rowWrap(row+1)][colWrap(col)])
        count++;
    if (board[rowWrap(row+1)][colWrap(col-1)])
        count++;
    if (board[rowWrap(row+1)][colWrap(col+1)])
        count++;
    return count;
}

// returns the wrapped value of x
int rowWrap(const int x)
{
    if (x >= ROWS)
        return 0;
    else if (x == -1)
        return ROWS -1;
    return x;
}

// returns the wrapped value of y
int colWrap(const int y)
{
    if (y >= COLS)
        return 0;
    else if (y == -1)
        return COLS-1;
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

void runLife(int board[][ROWS])
{

    while(1)
    {
        nextBoardState(board);
        printBoard(board);
        SLEEP;
    }
}

int main()
{
    int board[COLS][ROWS];
    initBoard(board, true);
    printBoard(board);
    runLife(board);
}