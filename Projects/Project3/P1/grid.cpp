#include "grid.h"
#include "dictionary.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<vector<string>> Grid::readMatrixFromFile(const string &fileName)
{
    vector<vector<string>> matrix;
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << fileName << endl;
        return matrix;
    }

    int rows, cols;
    file >> rows >> cols;
    file.ignore(); // Ignore the newline character after reading cols

    for (int i = 0; i < rows; ++i)
    {
        vector<string> row;
        for (int j = 0; j < cols; ++j)
        {
            string element;
            file >> element;
            row.push_back(element);
        }
        matrix.push_back(row);
    }
    return matrix;
}

void findMatches(Dictionary dict, Grid &grid)
{
    vector<string> matches;
}