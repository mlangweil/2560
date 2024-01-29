#include "response.h"
using namespace std;

Response::Response(int correct, int incorrect)
{
    this->numberCorrect = correct;
    this->numberIncorrect = incorrect;
}

bool operator==(Response &r1, Response &r2)
{
    return (r1.getNumberCorrect() == r2.getNumberCorrect());
}

std::ostream &operator<<(std::ostream &os, Response &response)
{
    os << "(" << response.getNumberCorrect() << ", " << response.getNumberIncorrect() << ")" << endl;
    return os;
}

int Response::getNumberCorrect() {
    return numberCorrect;
}

int Response::getNumberIncorrect() {
    return numberIncorrect;
}