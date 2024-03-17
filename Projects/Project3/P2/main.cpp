
#include "dictionary.h"
#include "grid.h"
#include "heap.h"
#include <iostream>

int main() {
    // int algo;
    // cout << "Provide the sorting algorithm you'd like to use 1. Selection, 2. Heap, 3.. Quicksort" << endl;
    // cin >> algo;
    // search(algo);
    Grid grid;
    Dictionary dict;
    grid.readMatrixFromFile("input15-2");
    dict.readWordsFromFile("dictionary-2");
    Heap<string> heap;
        vector<string> vec = dict.getWords();
        heap.heapSort(vec);
        dict.setWords(vec);
    dict.print();


}