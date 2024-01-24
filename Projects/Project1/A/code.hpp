#include <vector>
#ifndef CODE_HPP
#define CODE_HPP
class Code
{
public:
    int codeLength;
    int codeRange;
    std::vector<int> code;

    Code(int length, int range);
    int checkCorrect(Code code);
    int checkIncorrect(Code code);

private:
    void initializeCode(); // Corrected function declaration
};
#endif