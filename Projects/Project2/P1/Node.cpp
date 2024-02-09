#include "Card.h"

#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(Card c) : card(c), next(nullptr) {}
    Node(Card &c, Node *n) : card(c), next(n) {}
    Card card;
    Node *next;
};

#endif
