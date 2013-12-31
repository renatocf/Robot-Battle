// Default libraries
#include <stack>
#include <vector>
#include <iostream>

// Libraries
#include "Parser.hpp"
#include "Tokenizer.hpp"

Text& Parser::parse(std::string prompt /* = "> " */)
{
    // A Text is a set of sentences
    while(std::cout << prompt, tokenize(std::cin, text));
    
    // Take out last (and useless) sentence
    text.pop_back();
    
    // Jump line when receive EOF
    std::cout << std::endl;
    
    // Convert to posfix notation
    infix_to_posfix();
    
    return text;
}

Text& Parser::parse(std::istream& is)
{
    while(tokenize(is, text));
    
    // Take out last (and useless) sentence
    text.pop_back();
    
    // Convert to posfix notation
    infix_to_posfix();
    
    return text;
}

void Parser::reInit(std::istream& is)
{
    text = Text{};
}

void Parser::infix_to_posfix()
{
    std::stack<char,std::vector<char>> operators {};
    
    for(Sentence& sentence : text)
    {
        Sentence posfix;
        for(Token& t : sentence)
        {
            switch(t.type)
            {
                case Type::NUMBER:
                    posfix.push_back(t);
                    break;
                
                case Type::UNDEFINED:
                    std::cerr << "[INFIX_TO_POSFIX] This should not happen" << std::endl;
                    break;
                
                case Type::OPERATOR:
                    switch(t.o)
                    {
                        case '(': 
                            operators.push(t.o);
                            break;
                        
                        case '*': // next
                        case '/': // next
                        case '%': 
                            if(!operators.empty())
                            {
                                for(char op = operators.top(); !operators.empty(); op = operators.top()) 
                                {
                                    if(op == '(' || op == '+' || op == '-') break;
                                    posfix.push_back(Token {Type::OPERATOR, op});
                                    operators.pop();
                                }
                            }
                            operators.push(t.o);
                            break;
                             
                        case '+': // next
                        case '-':
                            if(!operators.empty())
                            {
                                for(char op = operators.top(); !operators.empty(); op = operators.top()) 
                                {
                                    if(op == '(') break;
                                    posfix.push_back(Token {Type::OPERATOR, op});
                                    operators.pop();
                                }
                            }
                            operators.push(t.o);
                            break;
                            
                        case ')':
                            if(!operators.empty())
                            {
                                for(char op = operators.top(); !operators.empty(); op = operators.top()) 
                                {
                                    if(op == '(') break;
                                    posfix.push_back(Token {Type::OPERATOR, op});
                                    operators.pop();
                                }
                                operators.pop(); // Take out '('
                            }
                            break;
                    }
                    break;
            }
        }
        
        while(!operators.empty())
        {
            posfix.push_back(Token {Type::OPERATOR, operators.top()});
            operators.pop();
        }
        
        sentence = std::move(posfix);
    }
}
