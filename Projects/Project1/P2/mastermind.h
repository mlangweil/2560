#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <iostream>
#include "code.hpp"
#include "response.h"

class Mastermind
{
private:
    Code secretCode;

public:
    Mastermind();
    Mastermind(int length, int range);
    Code humanGuess();
    Response getResponse(Code guessCode);
    bool isSolved(Response response);
    void playGame();
};

#endif 
