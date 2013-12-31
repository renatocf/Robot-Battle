// Default libraries
#include <iostream>

// Libraries
#include "Token.hpp"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 TOKEN                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
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
            os << "[TOKEN:Should not happen]";
    }
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                SENTENCE                                 
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
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

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  TEXT                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
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
