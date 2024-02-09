#include "Deck.h"
#include <vector>
#include <random>
using namespace std;
Deck::Deck()
{
    orderDeck();
}

Deck::~Deck()
{
    Node *currNode = front;
    while (currNode != nullptr)
    {
        Node *temp = currNode;
        currNode = currNode->next;
        delete temp;
    }
}
void Deck::orderDeck()
{
    Card spade(2, "Spade");
    Node *currNode = new Node(spade);

    Card club(2, "Club");
    Node *node3 = new Node(club, currNode);

    Card diamond(2, "Diamond");
    Node *node2 = new Node(diamond, node3);

    Card heart(2, "Heart");
    Node *node1 = new Node(heart, node2);

    front = node1;
    for (int i = 3; i <= 14; i++)
    {
        Card spade(i, "Spade");
        Node *node4 = new Node(spade);

        Card club(i, "Club");
        Node *node3 = new Node(club, node4);

        Card diamond(i, "Diamond");
        Node *node2 = new Node(diamond, node3);

        Card heart(i, "Heart");
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
    return i;
}
Node *Deck::getFront() const
{
    return front;
}

ostream &operator<<(ostream &out, const Deck &deck)
{
    Node *currNode = deck.getFront();
    while (currNode != nullptr)
    {
        out << currNode->card; // Using 'out' instead of 'cout'
        currNode = currNode->next;
    }
    return out;
}

bool contains(vector<int> vec, int num)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (num == vec[i])
        {
            return true;
        }
    }
    return false;
}

void Deck::shuffle()
{
    vector<Node *> nodes;
    vector<int> numbers;

    // Populate nodes vector with all nodes in the linked list
    Node *currNode = front;
    while (currNode != nullptr)
    {
        nodes.push_back(currNode);
        currNode = currNode->next;
    }

    // Seed the random number generator outside the loop
    srand((unsigned)time(NULL));

    while (numbers.size() != 52)
    {
        // Generate a random number between 0 and 51
        int random_number = rand() % 52;
        if (!contains(numbers, random_number))
        {
            numbers.push_back(random_number);
        }
    }

    // Rearrange nodes according to the randomly generated indices
    Node *newFront = nodes[numbers[0]];
    currNode = newFront;
    for (size_t i = 1; i < 52; ++i)
    {
        currNode->next = nodes[numbers[i]];
        currNode = currNode->next;
    }
    currNode->next = nullptr;

    // Update the front pointer of the linked list
    front = newFront;
}

