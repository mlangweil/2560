#include <iostream>
using namespace std;
#ifndef CARD_H
#define CARD_H

class Card
{
private:
    int value;
    string suit;

public:
    Card();
    Card(int val, string s);
    int getValue() const;
    void setValue(int val);
    void setSuit(string s);
    string getSuit() const;
    ostream &operator<<(ostream &out);
};

class Spade : public Card
{
public:
    Spade(int val);
};

class Diamond : public Card
{
public:
    Diamond(int val);
};

class Heart : public Card
{
public:
    Heart(int val);
};

class Club : public Card
{
public:
    Club(int val);
};

#endif