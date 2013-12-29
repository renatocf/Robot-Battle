#ifndef HPP_TOKEN_DEFINED
#define HPP_TOKEN_DEFINED

// Enum Type
enum class Type { UNDEFINED, NUMBER, OPERATOR };

// Aliases
using number_t    = int;
using operator_t  = char;

struct Token
{
    Type type;
    union {
        number_t   n;
        operator_t o;
    };
    
    Token() 
        : type{Type::UNDEFINED}, n{0} {}
    Token(Type t, number_t n) 
        : type{t}, n{n} {}
    Token(Type t, operator_t o) 
        : type{t}, o{o} {}
    
    ~Token() {}
    
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

#endif
