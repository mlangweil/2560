#include "code.hpp"
#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

Code::Code(int length, int range) {
    this->codeLength = length;
    this->codeRange = range;
	srand((unsigned) time(NULL));
    initializeCode();
}

void Code::initializeCode(){
    
    for (int i =0; i < codeLength; i++) {
    std::random_device rd;
    // Use the random_device to initialize the random number generator
    std::default_random_engine generator(rd());
    // Define a distribution for the range of random numbers you want
    std::uniform_int_distribution<int> distribution(1, codeRange);
    // Generate a random number
    int random_number = distribution(generator);
        cout<<random_number<<" ";
        guessList.push_back(random_number);
    }
    cout<<endl;
}

int Code::checkCorrect(Code code) {
    int correct = 0;
    for (int i = 0; i < code.codeLength; i++) {
        
        if (guessList[i] == code.guessList[i]) {
            correct+=1;
        }
    }
    return correct;
}

int Code::checkIncorrect(Code code) {
    int incorrect = 0;
    vector<int> tempList = code.guessList;
    for (int i = 0; i < code.codeLength; i++) {
        for (int j = 0; j < tempList.size(); j++) {
            if (code.guessList[i] == code.guessList[j]) {
            //erase
            break;
            }
        }
    }
    for (int i = 0; i < code.codeLength; i++) {
         for (int i = 0; i < this->codeLength; i++) {
        if (guessList[i] == code.guessList[i]) {
            incorrect+=1;
        }
    }
    }
    return incorrect;
}

