#include "mastermind.h"
#include <iostream>

int main() {
    int length;
    int range;
    cout<<"Enter the length of the code:"<<endl;
    cin>>length;
    cout<<"Enter the range of the code:"<<endl;
    cin>>range;
    Mastermind Mastermind(length, range);
    Mastermind.playGame();
    return 0;
}