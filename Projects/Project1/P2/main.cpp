#include "mastermind.h"
#include <iostream>

int main()
{
    int length;
    int range;
    cout << "Enter the length of the code:" << endl;
    errorHandle(length);
    cout << "Enter the range of the code:" << endl;
    errorHandle(range);
    Mastermind mastermind(length, range);
    mastermind.playGame();
    return 0;
}