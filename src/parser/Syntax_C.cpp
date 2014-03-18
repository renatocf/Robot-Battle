#include <iostream>
#include "Syntax_C.hpp"

std::ostream& parser::operator<<(std::ostream& os, const ExprC& exprC)
{
    exprC.print(0, ' ');
    return os;
}
