#include "mastermind.h"

Mastermind::Mastermind()
{
    Code newCode(5, 10);
    this->code = newCode;
}
Mastermind::Mastermind(int length, int range)
{
    Code newCode(length, range);
    this->code = newCode;
}

Code Mastermind::humanGuess()
{
    vector<int> guessVector;
    Code guessCode(code.getCodeLength(), code.getCodeRange());
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
    Response guessResponse(this->code.checkCorrect(guessCode), this->code.checkIncorrect(guessCode));
    return guessResponse;
}

bool Mastermind::isSolved(Response guessResponse)
{
    Response correctResponse(this->code.checkCorrect(this->code), this->code.checkIncorrect(this->code));
    return correctResponse == guessResponse;
}

void Mastermind::playGame()
{
    Code secretCode(this->codeLength, this->codeRange);
    secretCode.initializeCode();
    int numTries = 10;
    for (int i = 1; i <= numTries; i++)
    {
        Code guessCode;
        Response guessResponse;
        cout << "Input guess number " << i << ":" << endl;
        guessCode = this->humanGuess();
        guessResponse = this->getResponse(guessCode);

        if (this->isSolved(guessResponse))
        {
            cout << "Congrats! You guessed the code!" << endl;
            secretCode.printCode();
        }
        else if (i == numTries)
        {
            cout << "You failed!" << endl;
            secretCode.printCode();
        }
    }
}