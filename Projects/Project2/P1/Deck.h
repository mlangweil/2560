#include "Node.h"
#include <iostream>
using namespace std;

#ifndef DECK_H
#define DECK_H

class Deck
{
    Node *front;
    Deck();
    void orderDeck();
    ostream &operator<<(ostream &out);
};

#endif DECK_H