#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

int countSolutions;

bool isSafe(vector<vector<int>> &board, int row, int col)
{
    int n = board.size();

    // Check column above
    for (int i = 0; i < row; i++)
    {
        if (board[i][col] == 1)
        {
            return false;
        }
    }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; i--, j++)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }

    return true;
}

void solveNQueens(vector<vector<int>> &board, int row)
{
    int n = board.size();

    // Base case: All queens are placed
    if (row == n)
    {
        countSolutions++;
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col))
        {
            board[row][col] = 1;          // Place queen
            solveNQueens(board, row + 1); // Recur to place rest of the queens
            board[row][col] = 0;          // Backtrack
        }
    }
}

int main()
{
    vector<int> boardSizes = {4, 5, 6, 7, 8};

    for (int N : boardSizes)
    {
        vector<vector<int>> board(N, vector<int>(N, 0));
        countSolutions = 0;

        auto startTime = chrono::high_resolution_clock::now();
        solveNQueens(board, 0); // Start placing queens from the 0th row
        auto endTime = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsedTime = endTime - startTime;
        cout << "For board size " << N << "x" << N << ", number of possible solutions are: " << countSolutions << endl;
        cout << "Time taken: " << elapsedTime.count() << " ms\n"
             << endl;
    }

    return 0;
}
