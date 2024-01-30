#include "mastermind.h"

// Default constructor
Mastermind::Mastermind()
{
    // Create a secret code with default values (length = 5, range = 10)
    Code secretCode(5, 10);
    this->secretCode = secretCode;
}

// Overloaded constructor
Mastermind::Mastermind(int length, int range)
{
    // Create a new secret code with specified length and range
    Code newCode(length, range);
    this->secretCode = newCode;
}

// Function to get a human guess
Code Mastermind::humanGuess()
{
    vector<int> guessVector;
    // Create a guess code with the same length and range as the secret code
    Code guessCode(secretCode.getCodeLength(), secretCode.getCodeRange());
    for (int i = 0; i < guessCode.getCodeLength(); i++)
    {
        int val = 0;
        cout << "Enter element " << i + 1 << ":";
        cin >> val;
        guessVector.push_back(val);
    }
    guessCode.setVector(guessVector);
    return guessCode;
}

// Function to get the response for a guess
Response Mastermind::getResponse(Code guessCode)
{
    // Create a response object based on the correctness of the guess
    Response guessResponse(this->secretCode.checkCorrect(guessCode), this->secretCode.checkIncorrect(guessCode));
    return guessResponse;
}

// Function to check if the code is solved
bool Mastermind::isSolved(Response guessResponse)
{
    // Create a response representing the correct code
    Response correctResponse(this->secretCode.checkCorrect(this->secretCode), this->secretCode.checkIncorrect(this->secretCode));
    return correctResponse == guessResponse;
}

// Function to play the game
void Mastermind::playGame()
{
    // Initialize the secret code
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
        secretCode.printCode();
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
