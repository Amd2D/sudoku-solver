/*
* Sudoku solver using brute force algorithm (with backtracking) in C++
* Sudoku Rules:
* - Each row must contain 1 through 9, without repetition. 
* - Each column must contain 1 through 9, without repetition. 
* - Each subgrid must contain 1 through 9, without repetition. 
* The sum of every single row, column and subgrid must thus be equal to 45:
* (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 = 45)
*/

#include <iostream>
using std::cout;
using std::endl;

// Size of the matrix that will be used as a Sudoku grid
#define N 9

// Function used to print the Sudoku grid
void PrintGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << "\n";
    }
}

// Checks if move is legal and follows the Sudoku rules
bool isValid(int grid[N][N], int row, int col, int num)
{
    // Check row for the same number
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;

    // Check column for the same number
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;

    // Check subgrid (3x3 matrix) for the same number
    int startRow = row - row % 3,
        startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;
    
    // Return true if none of the rules for the current position are broken
    return true;
}

// Takes a partially filled grid and tries to solve it abiding by the Sudoku rules
bool SolveSudoku(int grid[N][N], int row = 0, int col = 0)
{
    // Check if last position has been reached and return true to prevent further backtracking
    if (row == N - 1 && col == N)
        return true;

    // Check if last column is reached and move on to the first column in the next row 
    if (col == N) {
        row++;
        col = 0;
    }

    // Check if the current position of the grid already contains a number and moves on to next column
    if (grid[row][col] != 0)
        return SolveSudoku(grid, row, col + 1);

    for (int num = 1; num <= N; num++)
    {
        // Check if move is valid using our isValid method
        if (isValid(grid, row, col, num))
        {
            // Placing a valid number in current empty position of the grid assuming it is the right one
            grid[row][col] = num;

            // Move on to next column
            if (SolveSudoku(grid, row, col + 1))
                return true;
        }

        // Removing the placed number if it was wrong
        grid[row][col] = 0;
    }

    // If Sudoku grid is unsolvable return false
    return false;
}

int main()
{
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

    cout << "Initial Sudoku Grid is: \n";
    PrintGrid(grid);
    cout << "-----------------" << "\n";

    if (SolveSudoku(grid)) {
        cout << "Solved Sudoku Grid is: \n";
        PrintGrid(grid);
    }  
    else {
        cout << "This Sudoku grid is unsolvable." << endl;
    }  

    return 0;
}