#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

class Response {
private:
    int numberCorrect;
    int numberIncorrect;

public:
    // Constructor
    Response(int correct = 0, int incorrect = 0);

    // Getter functions
    int getNumberCorrect();
    int getNumberIncorrect() ;

    // Overloaded operator==
    friend bool operator==(Response& r1, Response& r2);

    // Overloaded operator<<
    friend std::ostream& operator<<(std::ostream& os,  Response& response);
};

#endif // RESPONSE_H
