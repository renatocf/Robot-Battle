#include "Stackable.hpp"

std::ostream& 
stk::operator<<(std::ostream& os, const stk::Stackable& stk)
{
    os << stk.to_string();
    return os;
}

std::ostream& 
stk::operator<<(std::ostream& os, const stk::Stackable_ptr& stk)
{
    if(stk) os << stk->to_string();
    return os;
}
