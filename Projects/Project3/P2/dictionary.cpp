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
        word[0] = tolower(word[0]);
        words.push_back(word); // Store each word in the vector
    }

    file.close(); // Close the file
}

void Dictionary::setWords(vector<string> vec)
{
    this->words = vec;
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
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            // Compare strings while ignoring case of the first letter
            if (words[j] < words[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(words[i], words[minIndex]);
        }
    }
}

bool Dictionary::binarySearch(string word)
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

vector<string> Dictionary::getWords()
{
    return words;
}

int Dictionary::partition(vector<string> &arr, int low, int high)
{
    string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        // Compare strings while ignoring case of the first letter
        if (tolower(arr[j][0]) <= tolower(pivot[0]))
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort function for vector<string>
void Dictionary::quickSortHelper(vector<string> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(words, low, high);
        quickSortHelper(arr, low, pivotIndex - 1);
        quickSortHelper(arr, pivotIndex + 1, high);
    }
}

void Dictionary::quickSort()
{
    quickSortHelper(words, 0, words.size() - 1);
}
