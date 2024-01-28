#ifndef MASTERMIND_H
#define MASTERMIND_H

#include <iostream>
#include "code.hpp"

class Mastermind
{
private:
    Code code;

public:
    Mastermind();
    Mastermind(int length, int range);
    void humanGuess();
};

#endif // RESPONSE_H
