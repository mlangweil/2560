#include "Deck.h"
#include "Card.h"

Deck::Deck()
{
    orderDeck();
}

void Deck::orderDeck()
{
    Spade spade(1);
    Node *currNode = new Node(spade);

    Club club(1);
    Node *node3 = new Node(club, currNode);

    Diamond diamond(1);
    Node *node2 = new Node(diamond, node3);

    Heart heart(1);
    Node *node1 = new Node(heart, node2);

    front = node1;
    for (int i = 1; i <= 13; i++)
    {
        Spade spade(i);
        Node *node4 = new Node(spade);

        Club club(i);
        Node *node3 = new Node(club, node4);

        Diamond diamond(i);
        Node *node2 = new Node(diamond, node3);

        Heart heart(i);
        Node *node1 = new Node(heart, node2);
        currNode->next = node1;
        currNode = node4;
    }
}
int Deck::size() const
{
    Node *currNode = front;
    int i = 0;
    while (currNode->next != nullptr)
    {
        currNode = currNode->next;
        i++;
    }
}
ostream &Deck::operator<<(ostream &out)
{
    
}