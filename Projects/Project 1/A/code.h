#ifdef CODE_HPP
#define CODE_HPP
#include <vector>

class Code
{
public:
    int codeLength;
    int codeRange;
    std::vector<int> code;

    Code(int length, int range); // Corrected constructor declaration
    int checkCorrect(Code code);
    int checkIncorrect(Code code);

private:
    void initializeCode(); // Corrected function declaration
};
#endif
