// Default libraries
#include <iostream>

// Libraries
#include "Text.hpp"

std::ostream &operator<<(std::ostream &os, const Text& text)
{
    bool first = true;
    for(Sentence sent : text)
    {
        (first) ? first = false : os << std::endl;
        os << sent;
    }
    return os;
}
