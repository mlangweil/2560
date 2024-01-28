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

void Mastermind::humanGuess()
{
}