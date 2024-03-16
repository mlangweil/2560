#include <iostream>
#include <string>
#include <vector>
#include "dictionary.h"
#include <fstream>

using namespace std;

// Function to read words from a file and store them in a vector
void Dictionary::readWordsFromFile(const string &filename)
{
    ifstream file(filename); // Open the file

    if (!file.is_open())
    {
        cerr << "Failed to open the file: " << filename << std::endl;
    }

    string word;
    // Read words from the file until the end
    while (file >> word)
    {
        words.push_back(word); // Store each word in the vector
    }

    file.close(); // Close the file
}

void Dictionary::print()
{
    for (int i = 0; i < words.size(); i++)
    {
        cout << words[i] << " ";
    }
}

void Dictionary::selectionSort()
{
    int n = words.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (words[j] < words[minIndex]) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(words[i], words[minIndex]);
            }
        }
    }

bool Dictionary::binarySearch(string &word)
{
    int low = 0;
    int high = words.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (words[mid] == word)
        {
            return true; // Word found
        }
        else if (words[mid] < word)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return false; // Word not found
}

vector<string> Dictionary::getWords(){
    return words;
}