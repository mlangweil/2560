
#include "dictionary.h"
#include "grid.h"
#include "heap.h"
#include <iostream>

int main()
{
    int algo;
    cout << "Provide the sorting algorithm you'd like to use 1. Selection, 2. Heap, 3. Quicksort" << endl;
    cin >> algo;
    search(algo);
    
}