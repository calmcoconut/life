/* board state saves and manages the state of the board.
 - should be a 2D grid
 - random_state will accept 2 arguments, width and height of the board
 - dead_state will also accept 2 args, width and height, but init all 0's

 1. any live cells with 0 or 1 live neighbors becomes dead because of underpop
 2. any live cell with 2 or 3 live neighbors stays alive
 3. any live cell with more than 3 live neighbors becomes dead
 4. any dead cell with exactly 3 live neighbors becomes alive by reproduction

Note: purposefully have used arrays here instead of vectors.
      This is in order to foster confidence on pointers.
*/
#include "life.h"

class Board
{
private:
    int rows, columns;
    int **boardArr = NULL;

    int **create2dArray(unsigned rows, unsigned cols)
    {
        int **array2D = 0;
        array2D = new int *[rows];

        for (int h = 0; h < rows; h++)
        {
            array2D[h] = new int[cols];

            for (int w = 0; w < rows; w++)
            {
                array2D[h][w] = 0;
            }
        }
        return array2D;
    }

public:
    ~Board()
    {
        delete[] boardArr;
    }
    int **get_board()
    {
        return boardArr;
    }
    void dead_state(const int row, const int col)
    {
        rows = row;
        columns = col;
        boardArr = new int *[row];
        for (int i = 0; i < row; i++)
        {
            boardArr[i] = new int[col];
            for (int j = 0; j < col; j++)
            {
                boardArr[i][j] = 0;
            }
        }
    }
    void random_state(const int row, const int col)
    {
        rows = row;
        columns = col;
        srand(time(nullptr));
        boardArr = new int *[row];
        for (int i = 0; i < row; i++)
        {
            boardArr[i] = new int[col];
            for (int j = 0; j < col; j++)
            {
                boardArr[i][j] = rand() % 2;
            }
        }
    }
    int **next_board_state(int *arr, size_t rows, size_t cols)
    {
        int **nextBoard = create2dArray(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int neighbors = 0;
                // check immediate left-right neighbors
                if (j != 0)
                {
                    if (*((arr + (i)*cols - 1) + j) == 1)
                        neighbors += 1; //column left
                }
                if (j + 1 < cols)
                {
                    if (*((arr + (i)*cols + 1) + j) == 1)
                        neighbors += 1; //column right
                }
                // check rows and diagonals
                if (i != 0)
                {
                    // generally to access a 2d array with a pointer
                    // *((array+currentRow*totalColumnLength) + currentRow)
                    if (*((arr + (i - 1) * cols) + j) == 1)
                        neighbors += 1; //row above
                    if (j != 0)
                    {
                        if (*((arr + (i - 1) * cols) + j - 1) == 1)
                            neighbors += 1; // row diagonal up-left
                    }
                    if (j + 1 < cols)
                    {
                        if (*((arr + (i - 1) * cols) + j + 1) == 1)
                            neighbors += 1; // row diagonal up-right
                    }
                }
                if (i+1 <rows)
                {
                    if (*((arr + (i + 1) * cols) + j) == 1) 
                        neighbors += 1; //row below
                    
                    if (j-1 >0)
                    {
                        if (*((arr + (i + 1) * cols) + j-1) == 1) //diagonal below-left
                            neighbors += 1;
                    }
                    if (j+1 < columns)
                    {
                        if (*((arr + (i + 1) * cols) + j+1) == 1) //diagonal below-right
                            neighbors +=1;
                    }
                }
            }
            return nextBoard;
        }
        void render()
        {
            for (int i = 0; i < columns + 2; i++)
            {
                cout << "-";
            }
            cout << "\n";

            for (int i = 0; i < rows; i++)
            {
                cout << "|";
                for (int j = 0; j < columns; j++)
                {
                    if (boardArr[i][j])
                        cout << "#";
                    else
                        cout << " ";
                }
                cout << "|\n";
            }
            for (int i = 0; i < columns + 2; i++)
            {
                cout << "-";
            }
            cout << "\n";
        }
    };

    class BoardTest
    {
    public:
        void run_tests()
        {
            Board board;
            board.dead_state(5, 5);
            test_dead_board(board.get_board());
            test_state_board();
        }

    private:
        void test_dead_board(int *board[5])
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (board[i][j] != 0)
                    {
                        cout << "-FAIL test_dead_board\n";
                        return;
                    }
                }
            }
            cout << "+SUCCESS test_dead_board\n";
        }
        void test_state_board()
        {
            Board b;
            // testing dead board
            int init_board[][3] = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}};
            int expected_board[][3] = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}};
            b.next_board_state(init_board[0], 3, 3);
        }
    };

    int main()
    {
        BoardTest bt;
        bt.run_tests();
    }