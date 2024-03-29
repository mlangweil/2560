#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"
#include <cmath>

using namespace std;

typedef int ValueType;    // The type of the value in a cell
const int Blank = -1;     // Indicates that a cell is blank
const int SquareSize = 3; // The number of cells in a small square
// (usually 3). The board has
// SquareSize^2 rows and SquareSize^2
// columns.
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;
int numSolutions = 0;

class board
{
public:
    board(int);
    void clear();
    void initialize(ifstream &fin);
    void print();
    bool isBlank(int, int);
    ValueType getCell(int, int);
    void setCell(int, int, int);
    bool updateConflictVectors(int n, int i, int j);
    void initializeConflictVectors();
    bool addValueToCell(int n, int i, int j);
    bool isSolved();
    void clearCell(int n, int i, int j);
    void printConflicts();

private:
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    matrix<ValueType> value;
    matrix<bool> conf;
};

int squareNumber(int i, int j)
{
    return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

board::board(int sqSize)
    : value(BoardSize + 1, BoardSize + 1)
{
    clear();
}

void board::clear()
{
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
        }
}

void board::initializeConflictVectors()
{
    // Resize the conf matrix to the appropriate size
    conf.resize(BoardSize, BoardSize * 3);

    // Initialize conf matrix based on the values in the grid
    for (int i = 1; i <= BoardSize; i++) // LeftRight
    {
        for (int j = 1; j <= BoardSize; j++) // UpDown
        {

            int num = value[j][i];
            if (num != Blank)
            {
                // Set the corresponding cell in conf to true
                conf[num - 1][j - 1] = true;             // Rows
                conf[num - 1][BoardSize + j - 1] = true; // Columns

                conf[num - 1][(BoardSize * 2) + squareNumber(j,i)-1] = true; // Mini-Squares Z style

              
            }
        }
    }
}

bool board::updateConflictVectors(int n, int i, int j)
{
    if (conf[BoardSize + j][getCell(i, j) + 1] || conf[i][getCell(i, j) + 1] || conf[(BoardSize * 2) + (i + j) % 3][getCell(i, j) + 1])
    {
        return false;
    }
    conf[i][n] = true;
    conf[BoardSize + j][n] = true;
    conf[(BoardSize * 2) + (i + j) % 3][n] = true;
    return true;
}

bool board::addValueToCell(int n, int i, int j)
{
    if (updateConflictVectors(n, i, j))
    {
        value[i][j] = n;
        return true;
    }
    return false;
}

void board::clearCell(int n, int i, int j)
{
    value[i][j] = Blank;
    conf[i][getCell(i, j) + 1] = true;
    conf[BoardSize + j][getCell(i, j) + 1] = true;
    conf[(BoardSize * 2) + (i + j) % 3][getCell(i, j) + 1] = true;
}

bool board::isSolved()
{
    for (int i = 0; i < BoardSize * 3; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (!conf[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void board::initialize(ifstream &fin)
{
    char ch;
    clear();
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            if (ch != '.')
                setCell(i, j, ch - '0'); // Convert char to int
            else
                setCell(i, j, Blank);
        }
}

ostream &operator<<(ostream &ostr, vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
    return ostr;
}

ValueType board::getCell(int i, int j)
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}

void board::setCell(int i, int j, int val)
{
    value[i][j] = val;
}

bool board::isBlank(int i, int j)
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    return (getCell(i, j) == Blank);
}

void board::print()
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i - 1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j - 1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i, j))
                cout << " " << getCell(i, j);
            else
                cout << "-1";
            cout << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
}

void board::printConflicts()
{
    for (int j = 0; j < BoardSize * 3; j++)
    {
        if (j+BoardSize == BoardSize)
        {
            cout << "Rows" << endl;
        }
        else if (j+BoardSize == BoardSize * 2)
        {
            cout << "Columns" << endl;
        }
        else if (j+BoardSize == BoardSize * 3)
        {
            cout << "Squares" << endl;
        }

        cout << "[";
        for (int i = 0; i < 9; i++)
        {
            cout << conf[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

int main()
{
    ifstream fin;
    string fileName = "sudoku.txt";
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    try
    {
        while (fin && fin.peek() != 'Z')
        {
            board b1(SquareSize);
            b1.initialize(fin);
            b1.initializeConflictVectors();
            b1.print();
            b1.printConflicts();
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
