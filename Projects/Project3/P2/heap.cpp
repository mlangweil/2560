#include "heap.h"
#include "grid.h"
#include "dictionary.h"
#include <string>

template <typename T>
int Heap<T>::parent(int i)
{
    return (i - 1) / 2;
}

template <typename T>
int Heap<T>::left(int i)
{
    return 2 * i + 1;
}

template <typename T>
int Heap<T>::right(int i)
{
    return 2 * i + 2;
}

template <typename T>
void Heap<T>::maxHeapify(int i, int heapSize)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < heapSize && heap[l] > heap[largest])
        largest = l;

    if (r < heapSize && heap[r] > heap[largest])
        largest = r;

    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        maxHeapify(largest, heapSize);
    }
}

template <typename T>
void Heap<T>::buildMaxHeap()
{
    for (int i = heap.size() / 2 - 1; i >= 0; --i)
    {
        maxHeapify(i, heap.size());
    }
}

template <typename T>
T Heap<T>::getItem(int n)
{
    if (n >= heap.size())
        throw out_of_range("Index out of range");
    return heap[n];
}

template <typename T>
void Heap<T>::initializeMaxHeap(const vector<T> &items)
{
    heap = items;
    buildMaxHeap();
}

template <typename T>
void Heap<T>::heapSort(vector<string> &words)
{
    // Create a heap (max heap)
    heap = words;
    // Build max heap
    buildMaxHeap();

    // Perform heap sort
    for (int i = heap.size() - 1; i > 0; --i)
    {
        swap(heap[0], heap[i]);
        maxHeapify(0, i);
    }

    // Copy the sorted words back to the dictionary
    words = heap;
}

void search(int algo)
{
    string name;
    cout << "Provide the name of the grid file" << endl;
    cin >> name;

    Grid grid;
    Dictionary dict;
    dict.readWordsFromFile("dictionary-2");
    grid.readMatrixFromFile(name);
    if (algo == 1)
    {
        dict.selectionSort();
    }
    else if (algo == 2)
    {
        Heap<string> heap;
        vector<string> vec = dict.getWords();
        heap.heapSort(vec);
        dict.setWords(vec);
    }

    else if (algo == 3)
    {
        dict.quickSort();
    }
    else
    {
        cout << "Invalid selection" << endl;
    }

    // dict.print();
    findMatches(dict, grid);
}
