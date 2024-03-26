#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"

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

private:
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    matrix<ValueType> value;
    matrix<ValueType> conf;
};

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
    // rows
    conf.resize(BoardSize * 3, BoardSize);
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (value[i][j] == j + 1)
            {
                conf[i][j] = true;
            }
            else
            {
                conf[i][j] = false;
            }
        }
    }

    // cols
    for (int i = 0; i < BoardSize; i++)
    {
        for (int j = 0; j < BoardSize; j++)
        {
            if (value[j][i] == j + 1)
            {
                conf[j + BoardSize][i] = true;
            }
            else
            {
                conf[j + BoardSize][i] = false;
            }
        }
    }

    for (int i = 0; i < BoardSize; i += 3)
    { // Loop through mini-squares vertically
        for (int j = 0; j < BoardSize; j += 3)
        { // Loop through mini-squares horizontally
            for (int di = 0; di < 3; di++)
            { // Loop through rows within the mini-square
                for (int dj = 0; dj < 3; dj++)
                {                                    // Loop through columns within the mini-square
                    int num = value[i + di][j + dj]; // Get the number at the current cell
                    if (num >= 1 && num <= BoardSize)
                    { // Check if the number is valid
                        // Set the corresponding cell in conf to true based on the number
                        conf[j + (BoardSize * 2)][i + num - 1] = true;
                    }
                }
            }
        }
    }
}

bool board::updateConflictVectors(int n, int i, int j)
{
    if (conf[BoardSize + j][n + 1] || conf[i][n + 1] || conf[(BoardSize * 2) + (i + j) % 3][n + 1])
    {
        return false;
    }
    conf[i][n + 1] = true;
    conf[BoardSize + j][n + 1] = true;
    conf[(BoardSize * 2) + (i + j) % 3][n + 1] = true;
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

void board::clearCell(int n, int i, int j) {
    value[i][j] = Blank;
     conf[i][n + 1] = true;
    conf[BoardSize + j][n + 1] = true;
    conf[(BoardSize * 2) + (i + j) % 3][n + 1] = true;
}

bool board::isSolved() {
    for (int i =0; i < BoardSize *3; i++) {
        for (int j =0; j < BoardSize;j++) {
            if (!conf[i][j]) {
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

int squareNumber(int i, int j)
{
    return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
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
                cout << " " << getCell(i, j) << " ";
            else
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
        board b1(SquareSize);
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}

