
#include "dictionary.h"
#include "grid.h"
#include <iostream>

int main() {
    Dictionary dict;
    Grid grid;
    grid.readMatrixFromFile("input15-2");

    dict.readWordsFromFile("dictionary-2");
    findMatches(dict, grid);
    return 0;
}