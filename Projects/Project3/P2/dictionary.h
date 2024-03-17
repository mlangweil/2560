#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>

using namespace std;

class Dictionary
{
public:
    vector<string> words;
    void quicksort();
    void print();
    void readWordsFromFile(const string &filename);
    void selectionSort();
    bool binarySearch(string word);
    void quickSortHelper(vector<string> &arr, int low, int high);
    int partition(vector<string> &arr, int low, int high);
    void quickSort();
    void setWords(vector<string> vec);
    vector<string> getWords();
};
#endif