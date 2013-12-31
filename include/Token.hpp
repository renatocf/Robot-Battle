#ifndef HPP_TOKEN_DEFINED
#define HPP_TOKEN_DEFINED

// Default libraries
#include <vector>
#include <iostream>

// Enum Type
enum class Type { UNDEFINED, NUMBER, OPERATOR };

// Aliases
using number_t   = int;
using operator_t = char;

struct Token
{
    const Type type;
    const union {
        number_t   n;
        operator_t o;
    };
    
    // Constructors
    Token() 
        : type{Type::UNDEFINED}, n{0} {}
    Token(Type t, number_t n) 
        : type{t}, n{n} {}
    Token(Type t, operator_t o) 
        : type{t}, o{o} {}
    
    // Destructor
    ~Token() {}
    
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

using Sentence = std::vector<Token>;
std::ostream &operator<<(std::ostream &os, const Sentence& sent);

using Text = std::vector<Sentence>;
std::ostream &operator<<(std::ostream &os, const Text& text);

#endif
