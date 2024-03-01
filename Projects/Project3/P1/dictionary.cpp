#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dictionary.h"

using namespace std;

// Function to read words from a file and store them in a vector
vector<string> readWordsFromFile(const string &filename)
{
    vector<string> words;    // Vector to store words
    ifstream file(filename); // Open the file

    if (!file.is_open())
    {
        cerr << "Failed to open the file: " << filename << std::endl;
        return words; // Return an empty vector
    }

    string word;
    // Read words from the file until the end
    while (file >> word)
    {
        words.push_back(word); // Store each word in the vector
    }

    file.close(); // Close the file
    return words; // Return the vector of words
}

void Dictionary::print()
{
    for (int i = 0; i < words.size(); i++)
    {
        cout << words[i] << " ";
    }
}

void Dictionary::selectionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
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