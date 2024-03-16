
#include "dictionary.h"
#include "grid.h"

int main() {
    Dictionary dict;
    Grid grid;
    grid.readMatrixFromFile("input15-2.csv");
    dict.readWordsFromFile("dictionary-2(1).csv");

    findMatches(dict, grid);
    return 0;
}