#include "Stackable.hpp"

std::ostream& operator<<(std::ostream& os, const stk::Stackable& cmd)
{
    os << cmd.to_string();
    return os;
}
