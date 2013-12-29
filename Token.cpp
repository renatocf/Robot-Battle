// Default libraries
#include <iostream>

// Libraries
#include "Token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& t)
{
    switch(t.type)
    {
        case Type::NUMBER:
            os << "[NUMBER:" << t.n << "]";
            break;
        case Type::OPERATOR: 
            os << "[OPERATOR:" << t.o << "]";
            break;
        case Type::UNDEFINED: 
            os << "[UNDEFINED:]";
            break;
        default: 
            os << "[Should not happen]";
    }
    return os;
}
