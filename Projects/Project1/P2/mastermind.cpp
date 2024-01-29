#include "mastermind.h"

Mastermind::Mastermind()
{
    Code secretCode(5, 10);
    this->secretCode = secretCode;
}
Mastermind::Mastermind(int length, int range)
{
    Code newCode(length, range);
    this->secretCode = newCode;
}

Code Mastermind::humanGuess()
{
    vector<int> guessVector;
    Code guessCode(secretCode.getCodeLength(), secretCode.getCodeRange());
    for (int i = 0; i < guessCode.getCodeLength(); i++)
    {
        int val = 0;
        cout << "Enter element " << i + 1 << ":";
        cin >> val;
        cout << endl;
        guessVector.push_back(val);
    }
    guessCode.setVector(guessVector);
    return guessCode;
}

Response Mastermind::getResponse(Code guessCode)
{
    Response guessResponse(this->secretCode.checkCorrect(guessCode), this->secretCode.checkIncorrect(guessCode));
    return guessResponse;
}

bool Mastermind::isSolved(Response guessResponse)
{
    Response correctResponse(this->secretCode.checkCorrect(this->secretCode), this->secretCode.checkIncorrect(this->secretCode));
    return correctResponse == guessResponse;
}

void Mastermind::playGame()
{
    secretCode.initializeCode();
    int numTries = 10;
    for (int i = 1; i <= numTries; i++)
    {
        Code guessCode;
        Response guessResponse;
        cout << "Input guess number " << i << ":" << endl;
        guessCode = this->humanGuess();
        guessResponse = this->getResponse(guessCode);
        cout << guessResponse << endl;

        if (this->isSolved(guessResponse))
        {
            cout << "Congrats! You guessed the code!" << endl;
            secretCode.printCode();
            break;
        }
        else if (i == numTries)
        {
            cout << "You failed!" << endl;
            secretCode.printCode();
        }
    }
}