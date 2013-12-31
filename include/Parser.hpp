#ifndef HPP_PARSER_DEFINED
#define HPP_PARSER_DEFINED

// Default libraries
#include <string>

// Libraries
#include "Token.hpp"

class Parser
{
    private:
        Text text;
        
    public:
        // Text() 
            // : is{std::cin} 
        // {}
        // Text(std::istream is)
            // : is{is} {}
        
        // Getters
        const Text& getText() const { return text; }
        
        void  reInit (std::istream& is);
        Text& parse  (std::string prompt = "> ");
        Text& parse  (std::istream& is);
        
    private:
        void infix_to_posfix();
};


#endif
