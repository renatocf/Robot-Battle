// Default libraries
#include <string>
#include <iostream>

// Libraries
#include "Command.hpp"

std::ostream &operator<<(std::ostream &os, const Command& com)
{
    os << "[";
    (com.com != "") ? os << com.com : os << "none";
    os << ",";
    (com.arg != "") ? os << com.arg : os << "none";
    os << ",";
    (com.lab != "") ? os << com.lab : os << "none";
    os << "]";
    return os;
}
