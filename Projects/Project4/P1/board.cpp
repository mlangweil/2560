#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
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
    ValueType getCell(int, int, matrix<ValueType> &);
    void setCell(int i, int j, int val, matrix<ValueType> &confMatrix);
    void initConf();
    void printConf();
    void printMatrix(matrix<ValueType> &);
    void checkConflicts();

private:
    matrix<ValueType> value;
    matrix<ValueType> confRow; // Conflicts matrix for rows
    matrix<ValueType> confCol; // Conflicts matrix for columns
    matrix<ValueType> confSq;  // Conflicts matrix for squares
};

board::board(int sqSize)
    : value(BoardSize + 1, BoardSize + 1),
      confRow(BoardSize + 1, BoardSize + 1),
      confCol(BoardSize + 1, BoardSize + 1),
      confSq(BoardSize + 1, BoardSize + 1)
{
    clear();
}

int squareNumber(int i, int j)
{
    return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}
void board::clear()
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
            confRow[i][j] = 0; // Initialize all conflict matrices to 0
            confCol[i][j] = 0;
            confSq[i][j] = 0;
        }
    }
}

void board::initConf()
{
    // Initialize all conflict matrices to 0
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            confRow[i][j] = 0;
            confCol[i][j] = 0;
            confSq[i][j] = 0;

            int num = getCell(i, j, value);
            if (!isBlank(i, j))
            {
                checkConflicts();
            }
        }
    }
}

void board::initialize(ifstream &fin)
{
    char ch;
    clear();
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            // If the read char is not Blank
            if (ch != '.')
                setCell(i, j, ch - '0', value); // Convert char to int
        }
    }
}

void board::checkConflicts()
{
    // Initialize variables
    int index = 0, square = 0;
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
            {
                // Return the value in the cell
                index = getCell(i, j, value);
                // Return what square the current index is in
                square = squareNumber(i, j);
                // If the cell isn't blank, update the conflict vectors
                if (index != Blank)
                {
                    setCell(i, index, true, confRow);
                    setCell(j, index, true, confCol);
                    setCell(square, index, true, confSq);
                }
            }
            else
            {
                throw rangeError("bad value in GetCell");
            }
        }
    }
}



ostream &operator<<(ostream &ostr, vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
}

ValueType board::getCell(int i, int j, matrix<ValueType> &confMatrix)
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
    {
        return confMatrix[i][j];
    }
    else
    {
        throw rangeError("bad value in getCell");
    }
}

void board::setCell(int i, int j, int val, matrix<ValueType> &confMatrix)
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
    {
        confMatrix[i][j] = val;
    }
    else
    {
        throw rangeError("bad value in setCell");
    }
}

bool board::isBlank(int i, int j)
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    return (getCell(i, j, value) == Blank);
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
                cout << " " << getCell(i, j, value);
            else
                cout << Blank;
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

void board::printConf()
{
    cout << "Rows:" << endl;
    printMatrix(confRow);

    cout << "Cols:" << endl;
    printMatrix(confCol);

    cout << "Squares:" << endl;
    printMatrix(confSq);
}

void board::printMatrix(matrix<ValueType> &confMatrix)
{
    for (int i = 1; i <= BoardSize; i++)
    {
        cout << "[";
        for (int j = 1; j <= BoardSize; j++)
        {
            cout << getCell(i, j, confMatrix) << " ";
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
        board b1(SquareSize);

        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.initConf();
            b1.print();
            b1.printConf();
            b1.print();
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
