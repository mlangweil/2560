#include "Deck.h"
#include <iostream>
using namespace std;

int main()
{
    Deck deck;
    cout << "Ordered deck" << endl;
    cout << deck;
    deck.shuffle();
    cout << endl;
    cout << "Shuffled deck" << endl;
    cout << deck;
    return 0;
}