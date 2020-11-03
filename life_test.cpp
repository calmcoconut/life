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

void next_board_state_test(int board[][ROWS])
{
    int test_b[COLS][ROWS];
    initBoard(test_b, 0);
    for (int i=0; i<ROWS;i++)
    {
        for (int j=0; j<COLS; j++)
        {
            if (countNeighbors(test_b,j,i) != 0)
            {
                cout<<"FAILED next_board_state_test: dead board: neighbors not 0, coords, "<<i<<", "<<j<<"\n";
                return;
            }
        }
    }
    cout<<"\nSUCCESS: next_board_state_test: dead board\n";
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
    next_board_state_test(board);

    return 0;
}