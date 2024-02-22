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
    Card(int val, string s);
    Card(const Card &other);
    int getValue() const;
    void setValue(int val);
    void setSuit(string s);
    string getSuit() const;
    friend ostream &operator<<(ostream &out, const Card &card);
};

#endif