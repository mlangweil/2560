#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include "dictionary.h"
using namespace std;

class Grid {
public:
vector<vector<string>> matrix;
void readMatrixFromFile(const string& fileName);
vector<vector<string>> getMatrix();
void print();
};

void findMatches(Dictionary &dict, Grid &grid);
#endif