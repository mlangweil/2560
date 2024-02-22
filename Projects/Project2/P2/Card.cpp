#include "Card.h"

Card::Card(int val, string s)
{
    this->value = val;
    this->suit = s;
}

Card::Card(const Card &other) {
    this->value = other.value;
    this->suit = other.suit;
}

int Card::getValue() const
{
    return this->value;
}

string Card::getSuit() const
{
    return this->suit;
}

void Card::setSuit(string s)
{
    this->suit = s;
}

void Card::setValue(int val)
{
    this->value = val;
}

ostream &operator<<(ostream &out, const Card &card)
{
    if (card.getValue() > 10)
    {
        string name;
        if (card.getValue() == 11)
        {
            name = "Jack";
        }
        else if (card.getValue() == 12)
        {
            name = "Queen";
        }
        else if (card.getValue() == 13)
        {
            name = "King";
        }
        else if (card.getValue() == 14)
        {
            name = "Ace";
        }
        out << name << " of " << card.getSuit()<<"'s" << endl;
    }
    else
    {
        out << card.getValue() << " of " << card.getSuit()<<"'s" << endl;
    }
    return out;
}

