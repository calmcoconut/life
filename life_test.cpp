#ifndef life
#define life
#include "life.cpp"
#endif

void emptyBoardTest(int board[][ROWS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] != 0)
            {
                cout << "\nFAILED: emptyBoardTest\n";
                return;
            }
        }
    }
    cout << "\nSUCCESS: emptyBoardTest\n";
}

void row_wrap_test()
{
    //test 0
    if(ROWS-1 == rowWrap(-1) && rowWrap(ROWS) == 0)
    {
        cout<<"\nSUCCESS: row_wrap_test\n";
        return;
    }
    cout<<"\nFAILED: row_wrap_test\n";
}
void col_wrap_test()
{
    if(COLS-1 == colWrap(-1) && colWrap(COLS) == 0)
    {
        cout<<"\nSUCCESS: col_wrap_test\n";
        return;
    }
    cout<<"\nFAILED: col_wrap_test\n";
}
void test_wrap()
{
    //test all edge cases
    row_wrap_test();
    col_wrap_test();
}

void next_board_state_test_dead()
{
    int test_b[COLS][ROWS];
    initBoard(test_b, 0);
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (countNeighbors(test_b, j, i) != 0)
            {
                cout << "FAILED next_board_state_test: dead board: neighbors not 0, coords, " << i << ", " << j << "\n";
                return;
            }
        }
    }
    cout << "\nSUCCESS: next_board_state_test: dead board\n";
}

void next_board_state_test(int board[][ROWS], int expected[][ROWS])
{
    nextBoardState(board);
    for (int i=0; i<ROWS;i++)
    {
        for (int j=0; j<COLS; j++)
        {
            if (board[i][j] != expected[i][j])
            {
                cout << "FAILED next_board_state_test: failure of matching values at coords " << i << ", " << j << "\n";
                cout << "actual board:\n";
                printBoard(board);
                cout << "\n expected board:\n";
                printBoard(expected);
                return;
            }
        }
    }
    cout<<"\nSUCCESS: next_board_state_test\n";
}

int main()
{
    int board[COLS][ROWS];
    initBoard(board, 0);
    emptyBoardTest(board);
    printBoard(board);
    initBoard(board, 1);
    cout<<"next test is expected to fail:";
    emptyBoardTest(board);
    printBoard(board);
    test_wrap();
    next_board_state_test_dead();
    // set board for next state test
    initBoard(board, 0);
    board[0][2] = 1;
    board[1][1] = 1;
    board[1][2] = 1;
    int expected_next_board[ROWS][COLS] = {
        {1,1,1}
        ,{1,1,1}
        ,{1,1,1}
    };
    next_board_state_test(board,expected_next_board);
    initBoard(expected_next_board,0);
    next_board_state_test(board,expected_next_board);
    return 0;
}