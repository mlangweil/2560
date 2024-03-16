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
    void readWordsFromFile(const string &filename);
    void selectionSort();
    bool binarySearch(string& word);
    vector<string> getWords();
};
#endif