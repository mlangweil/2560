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
    bool isSolved();
    void updateCell(int, int, int);
    bool addValueToCell(int, int, int);
    void clearCell(int, int);
    bool solve();
    bool solveHelper(int, int);
    void calculateAvgCalls();
    int currPasses = 0;

private:
    matrix<ValueType> value;
    matrix<ValueType> confRow; // Conflicts matrix for rows
    matrix<ValueType> confCol; // Conflicts matrix for columns
    matrix<ValueType> confSq;  // Conflicts matrix for squares
    vector<int> numPasses;
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

// initializes conflict vectors
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

// loops through each value in the matrix and updates the conflict vectors
void board::checkConflicts()
{

    // Iterate through each cell in the board
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            int num = getCell(i, j, value);
            if (!isBlank(i, j))
            {
                updateCell(i, j, num); // Update conflicts for the cell
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

// receives the value of a cell given indexes and a matrix
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

// sets the value of a cell given indexes and a matrix
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

// adds a value to a cell and updates conflict vectors
bool board::addValueToCell(int i, int j, int num)
{
    if (getCell(i, j, value) == Blank)
    {
        updateCell(i, j, num);
    }
}

// sets the value in the conflict vector to 0 and makes the cell blank
void board::clearCell(int i, int j)
{
    int num = getCell(i, j, value);
    int square = squareNumber(i, j);

    if (!isBlank(i, j))
    {
        // Clear the conflict matrices for the cell
        setCell(i, num, 0, confRow);
        setCell(j, num, 0, confCol);
        setCell(square, num, 0, confSq);
    }

    // Clear the cell value
    setCell(i, j, Blank, value);
}

// updates cell only if a given number appears in the indexes of value and that cell is blank
void board::updateCell(int i, int j, int num)
{
    int square = squareNumber(i, j);
    if (num != Blank && !getCell(i, num, confRow) && !getCell(j, num, confCol) && !getCell(square, num, confSq))
    {
        // If the number doesn't conflict with row, column, or square
        setCell(i, num, true, confRow); // Update conflict matrices
        setCell(j, num, true, confCol);
        setCell(square, num, true, confSq);
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

// checks to see if any cell is blank AND if every value in the conflict is true
bool board::isSolved()
{
    int index = 0, square = 0;
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            index = getCell(i, j, value);
            if (index == Blank)
            {
                return false; // If any cell is blank, Sudoku is not solved
            }
            square = squareNumber(i, j);

            // Check if the number in the cell exists in its corresponding row, column, and square
            if (!getCell(i, index, confRow) || !getCell(j, index, confCol) || !getCell(square, index, confSq))
            {
                return false;
            }
        }
    }
    return true;
}

bool board::solveHelper(int row, int col)
{
    currPasses++;
    if (row == BoardSize + 1)
    {
        return true; // If all rows are filled, the Sudoku is solved
    }

    if (!isBlank(row, col))
    {
        // If the cell is already filled, move to the next cell
        int nextRow = row, nextCol = col + 1;
        if (nextCol > BoardSize)
        {
            nextCol = 1;
            nextRow++;
        }
        return solveHelper(nextRow, nextCol);
    }

    // Try placing numbers from 1 to 9 in the current empty cell
    for (int num = MinValue; num <= MaxValue; num++)
    {
        if (getCell(row, num, confRow) == 0 &&
            getCell(col, num, confCol) == 0 &&
            getCell(squareNumber(row, col), num, confSq) == 0)
        {
            updateCell(row, col, num);     // Update conflicts
            setCell(row, col, num, value); // Set the cell value

            int nextRow = row, nextCol = col + 1;
            if (nextCol > BoardSize)
            {
                nextCol = 1;
                nextRow++;
            }

            if (solveHelper(nextRow, nextCol))
            {
                return true;
            }

            // Backtrack if the current placement doesn't lead to a solution
            clearCell(row, col); // Clear the cell value and conflicts
        }
    }

    return false;
}

bool board::solve()
{
    bool solve = false;
    solve = solveHelper(1, 1); // Start solving from the first cell
    numPasses.push_back(currPasses);
    return solve;
}

// calculates the average recursive calls
void board::calculateAvgCalls()
{
    int numCalls = 0;
    for (auto num : numPasses)
    {
        numCalls += num;
    }
    numCalls = numCalls / numPasses.size();
    cout << "The average number of recursive calls are " << numCalls << "." << endl;
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
        int num = 0;

        while (fin && fin.peek() != 'Z')
        {
            num++;
            cout << "Board " << num << ":" << endl;
            b1.initialize(fin);
            b1.initConf();
            b1.print();
            b1.solve();
            b1.print();
            cout << "The number of recursive calls were " << b1.currPasses << "." << endl;
            b1.clear();
            cout << endl;
        }
        b1.calculateAvgCalls();
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
