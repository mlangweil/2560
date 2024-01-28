#include "response.h"
using namespace std;

bool operator==(const Response &r1, const Response &r2)
{
    return (r1.numberCorrect == r2.numberCorrect) && (r1.numberIncorrect == r2.numberIncorrect);
}

std::ostream &operator<<(std::ostream &os, const Response &response)
{
    os << "(" << response.getNumberCorrect() << ", " << response.getNumberIncorrect() << ")" << endl;
    return os;
}