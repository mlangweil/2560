#ifndef GRID_H
#define GRID_H
#include <vector>
using namespace std;

class Grid {
public:
vector<vector<int>> matrix;
vector<vector<string>> readMatrixFromFile(const string& fileName);
};
#endif