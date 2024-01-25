#include "code.hpp"
#include <iostream>

using namespace std;

int main() {
    Code code(4,4);
    Code code1(4,4);
    cout<<code.checkCorrect(code1)<<endl;;
    return 0;
}