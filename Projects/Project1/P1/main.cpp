#include "code.hpp"
#include <iostream>

using namespace std;

int main()
{
    vector<int> guessVector1 = {5, 0, 3, 2, 6};
    vector<int> guessVector2 = {2, 1, 2, 2, 2};
    vector<int> guessVector3 = {1, 3, 3, 4, 5};

    Code guess1(5, 4);
    Code guess2(5, 4);
    Code guess3(5, 3);
    guess1.setCode(guessVector1);
    guess2.setCode(guessVector2);
    guess3.setCode(guessVector3);

    Code mastermindCode(5, 4);
    mastermindCode.initializeCode();

    vector<Code> guesses = {guess1, guess2, guess3};
    mastermindCode.printCode();

    for (auto guess : guesses)
    {
        cout << mastermindCode.checkCorrect(guess) << ", " << mastermindCode.checkIncorrect(guess) << endl;
    }

    return 0;
}