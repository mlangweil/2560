
#include "dictionary.h"
#include "grid.h"
#include <iostream>

int main()
{
    string file;
    cout<<"Input the file name of the grid"<<endl;
    cin>>file;
    Dictionary dict;
    Grid grid;
    dict.readWordsFromFile("dictionary-2");
    grid.readMatrixFromFile(file);
    dict.selectionSort();
    findMatches(dict, grid);
    
}