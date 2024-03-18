#include "grid.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Grid::readMatrixFromFile(const string &fileName)
{

    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << fileName << endl;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore(); // Ignore the newline character after reading cols

    matrix.resize(rows);
    for (int i = 0; i < rows; ++i)
    {
        matrix[i].resize(cols);
        for (int j = 0; j < cols; ++j)
        {
            file >> matrix[i][j];
        }
    }
}

vector<vector<string>> Grid::getMatrix()
{
    return matrix;
}

// Function to print the matrix
void Grid::print()
{
    for (const auto &row : matrix)
    {
        for (const auto &element : row)
        {
            cout << element << " ";
        }
        cout << endl;
    }
}
void findMatches(Dictionary &dict, Grid &grid)
{
    vector<string> words = dict.getWords();

    int numRows = grid.getMatrix().size();
    int numCols = grid.getMatrix()[0].size();

    // Define directions: right, down, diagonal right-down, diagonal left-down
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    // Iterate over each cell in the grid
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            // Check each direction
            for (auto &dir : directions)
            {
                int dRow = dir[0];
                int dCol = dir[1];
                string currentWord = "";
                int r = row, c = col;
                while (r >= 0 && r < numRows && c >= 0 && c < numCols)
                {
                    vector<string> mat = grid.getMatrix()[r];
                    currentWord += mat[c];
                    if (dict.binarySearch(currentWord))
                    {
                        cout << currentWord << endl;
                    }
                    r += dRow;
                    c += dCol;
                }
            }
        }
    }
}