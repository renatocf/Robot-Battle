#include <iostream>
#include "Syntax_C.hpp"

std::ostream& parser::operator<<(std::ostream& os, const ArithC& arithC)
{
    arithC.print(0, ' ');
    return os;
}
