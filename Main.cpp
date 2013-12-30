// Default libraries
#include <stack>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Libraries
#include "Prog.hpp"
#include "Token.hpp"
#include "Grammar.hpp"
#include "Tokenizer.hpp"

static const char EOL = ';';

// Sentence and poiter to it

Text &infix_to_posfix(Text& sentences);
Prog posfix_to_asm(Text& sentences);
inline void print_sentence(Text& sentences);

int main()
{
    cout << "Hello, World" << endl;
    string input;
    
    // Vector representing sentences (separated by ;)
    Text text { Sentence{} };
    
    // while(cout << "> ", tokenize(cin, text));
    
    while(cout << "> ", getline(cin, input))
    {
        for(auto c : input)
        {
            // Get the last set of tokens
            Sentence& sentence = text.back();
            
            // Skip
            if     (c == ' ' ) continue;
            else if(c == '\t') continue;
            else if(c == '\v') continue;
            else if(c == '\n') continue;
            else if(c == EOL)
            {
                text.push_back(Sentence{});
            }
            else if(c >= '0' && c <= '9')
            {
                if(sentence.empty() 
                || sentence.back().type != Type::NUMBER)
                    sentence.push_back(Token {Type::NUMBER, 0});
                
                Token& t = sentence.back();
                t.n = t.n * 10 + static_cast<int>(c-'0');
            }
            else 
            {
                char op;
                switch(c)
                {
                    case ')': op = ')'; break;
                    case '+': op = '+'; break;
                    case '-': op = '-'; break;
                    case '*': op = '*'; break;
                    case '/': op = '/'; break;
                    case '%': op = '%'; break;
                    case '(': op = '('; break;
                    default: 
                        cerr << "Unidentified token \"" << c << "\"" << endl;
                        text.pop_back();
                        text.push_back(Sentence{});
                        continue;
                }
                sentence.push_back(Token { Type::OPERATOR, op });
            }
        }
    }
    
    // Take out last (and useless) sentence
    // sentences.pop_back();
    text.pop_back();
    
    if(cin.bad()) 
    {
        cerr << "[MAIN] IO error" << endl;
        return -1;
    }
    if(!cin.eof()) 
    {
        cerr << "[MAIN] Unknown error" << endl;
        return -1;
    }
    
    cout << endl;
    
    Prog prog { posfix_to_asm(infix_to_posfix(text)) };
    cout << prog << endl;
    
    return 0;
}

Text& infix_to_posfix(Text& text)
{
    stack<char,vector<char>> operators {};
    
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
                    cerr << "[INFIX_TO_POSFIX] This should not happen" << endl;
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
    
    return text;
}

Prog posfix_to_asm(Text& text)
{
    Prog prog {};
    
    for(Sentence& sentence : text)
        for(Token& t : sentence)
            switch(t.type)
            {
                case Type::NUMBER:
                    prog.push_back(Command { "PUSH", std::to_string(t.n) });
                    break;
                
                case Type::OPERATOR:
                    prog.push_back(Command { assembly_symbol_table[t.o] });
                    break;
                
                case Type::UNDEFINED:
                    cerr << "[POSFIX_TO_ASM] This should not happen" << endl;
                    break;
            }
    
    return prog;
}
           
inline void print_sentence(Text& text)
{
    for(Sentence& sentence : text)
        for(Token& t : sentence)
            cout << "    " << t << endl;
}
