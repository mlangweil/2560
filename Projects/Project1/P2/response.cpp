#include "response.h"
using namespace std;

// Constructor with parameters
Response::Response(int correct, int incorrect)
{
    this->numberCorrect = correct;
    this->numberIncorrect = incorrect;
}

// Overloaded equality operator
bool operator==(Response &r1, Response &r2)
{
    return (r1.getNumberCorrect() == r2.getNumberCorrect());
}

// Overloaded output stream operator
std::ostream &operator<<(std::ostream &os, Response &response)
{
    os << "(" << response.getNumberCorrect() << ", " << response.getNumberIncorrect() << ")" << endl;
    return os;
}

// Getter for the number of correct elements
int Response::getNumberCorrect() {
    return numberCorrect;
}

// Getter for the number of incorrect elements
int Response::getNumberIncorrect() {
    return numberIncorrect;
}
