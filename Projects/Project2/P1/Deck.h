#include "Node.cpp"
#include <iostream>
using namespace std;

#ifndef DECK_H
#define DECK_H

class Deck
{
public:
    Node *front;
    Deck();
    void orderDeck();
    ostream &operator<<(ostream &out);
    int size() const;
};

#endif