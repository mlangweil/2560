#include <vector>
#include <set>
#ifndef CODE_HPP
#define CODE_HPP
using namespace std;
class Code
{
public:
    int codeLength;
    int codeRange;
    vector<int> guess;

    Code(int length, int range);
    int checkCorrect(Code code);
    int checkIncorrect(Code code);
    void setCode(vector<int> newGuess);
    void initializeCode(); // Corrected function declaration
    void printCode();

};
#endif