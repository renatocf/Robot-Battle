// Default libraries
#include <iostream>

// Libraries
#include "Sentence.hpp"

std::ostream &operator<<(std::ostream &os, const Sentence& sent)
{
    bool first = true;
    for(Token token : sent)
    {
        (first) ? first = false : os << " ";
        os << token;
    }
    return os;
}
