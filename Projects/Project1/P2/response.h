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
    int getNumberCorrect() const;
    int getNumberIncorrect() const;

    // Setter functions
    void setNumberCorrect(int correct);
    void setNumberIncorrect(int incorrect);

    // Overloaded operator==
    friend bool operator==(const Response& r1, const Response& r2);

    // Overloaded operator<<
    friend std::ostream& operator<<(std::ostream& os, const Response& response);
};

#endif // RESPONSE_H
