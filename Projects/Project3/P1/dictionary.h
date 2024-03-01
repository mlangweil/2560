#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>

using namespace std;

class Dictionary
{
public:
    vector<string> words;
    void print();
    vector<string> readWordsFromFile(const string &filename);
    void selectionSort(vector<int>& arr);
    bool binarySearch(string& word);
};
#endif