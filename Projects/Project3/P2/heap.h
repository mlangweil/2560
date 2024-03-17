#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Heap {
private:
    vector<T> heap;

    int parent(int i);
    int left(int i);
    int right(int i);

    void maxHeapify(int i, int heapSize);
    void buildMaxHeap();

public:
    Heap() {}
    T getItem(int n);
    void initializeMaxHeap(const vector<T>& items);
    void heapSort(vector<string> &words);
};

void search(int algo);

#endif // HEAP_H
