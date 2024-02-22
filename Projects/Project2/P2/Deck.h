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
    ~Deck();
    void orderDeck();
    void shuffle();
    friend ostream &operator<<(ostream &out, const Deck &deck);
    int size() const;
    Node *getFront() const;
    Card deal();
    void replace(Card &card);
};

void playFlip();

#endif