#ifndef life
#define life
#include "life.cpp"
#endif

void emptyBoardTest(int board[][ROWS])
{
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            if (board[i][j] != 0)
            {
                cout<<"\nFAILED: emptyBoardTest\n";
                return;
            }
        }
    }
    cout<<"\nSUCCESS: emptyBoardTest\n";
}

int main()
{
    int board[COLS][ROWS];
    initBoard(board, 0);
    emptyBoardTest(board);
    printBoard(board);
    initBoard(board, 1);
    emptyBoardTest(board);
    printBoard(board);
    return 0;
}