#include "Card.h"

Card::Card(int val, string s)
{
    this->value = val;
    this->suit = s;
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

ostream &Card::operator<<(ostream &out)
{
    if (this->value > 10)
    {
        string name;
        if (this->value == 11)
        {
            name = "Jack";
        }
        else if (this->value == 12)
        {
            name = "Queen";
        }
        else if (this->value == 13)
        {
            name = "King";
        }
        else if (this->value == 14)
        {
            name = "Ace";
        }
        out << name << " of " << this->suit << endl;
    }
    else
    {
        out << this->value << " of " << this->suit << endl;
    }
}

Spade::Spade(int val)
{
    Card(val, "Spade");
}

Club::Club(int val)
{
    Card(val, "Club");
}

Diamond::Diamond(int val)
{
    Card(val, "Diamond");
}

Heart::Heart(int val)
{
    Card(val, "Heart");
}