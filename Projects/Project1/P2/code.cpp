#include "code.hpp"
#include <cstdlib>
#include <iostream>
#include <random>
#include <set>
using namespace std;

Code::Code(int length, int range)
{
    this->codeLength = length;
    this->codeRange = range;
}

void Code::initializeCode()
{
    srand((unsigned)time(NULL));

    for (int i = 0; i < codeLength; i++)
    {
        std::random_device rd;
        // Use the random_device to initialize the random number generator
        std::default_random_engine generator(rd());
        // Define a distribution for the range of random numbers you want
        std::uniform_int_distribution<int> distribution(1, codeRange);
        // Generate a random number
        int random_number = distribution(generator);
        guess.push_back(random_number);
    }
}

int Code::checkCorrect(Code code)
{
    int correct = 0;
    for (int i = 0; i < code.codeLength; i++)
    {

        if (guess[i] == code.guess[i])
        {
            correct += 1;
        }
    }
    return correct;
}

// checks if the guess and code have the same elements, but in different indexes
int Code::checkIncorrect(Code code)
{
    set<int> thisCode;
    set<int> thatGuess;
    int incorrect = 0;

    // creates new sets without the elements in common
    for (int i = 0; i < codeLength; i++)
    {
        if (guess[i] != code.guess[i])
        {
            thisCode.insert(this->guess[i]);
            thatGuess.insert(code.guess[i]);
        }
    }

    // iterates through each set (regardless of size) and counts the number of common elements
    for (auto element1 : thisCode)
    {
        for (auto element2 : thatGuess)
        {
            if (element1 == element2)
            {
                incorrect++;
                break;
            }
        }
    }
    return incorrect;
}

// sets the guess of a Code to the given vector
void Code::setVector(vector<int> newGuess)
{
    this->guess = newGuess;
}

// prints the code
void Code::printCode()
{
    cout << "Secret code: ";
    for (int i = 0; i < codeLength; i++)
    {
        cout << guess[i] << " ";
    }
    cout << endl;
}

int Code::getCodeLength() {
    return this->codeLength;
}

int Code::getCodeRange() {
    return this->codeRange;
}

