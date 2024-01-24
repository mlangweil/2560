#include "code.hpp"
#include <cstdlib>

Code::Code(int length, int range) {
    this->codeLength = length;
    this->codeRange = range;
}

void Code::initializeCode(){
    for (int i =0; i < codeLength; i++) {
        code.push_back(rand() % (codeRange+1));
    }
}

