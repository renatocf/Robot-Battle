// Default libraries
#include <stack>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Libraries
#include "Token.hpp"
#include "Colors.hpp"
#include "Grammar.hpp"
#include "Prog.hpp"
#include "Sentence.hpp"
#include "Text.hpp"

static const char EOL = ';';

// Sentence and poiter to it
using pSentence = unique_ptr<vector<Token>>;

void infix_to_posfix(vector<pSentence>& sentences);
Prog posfix_to_asm(vector<pSentence>& sentences);
inline void print_sentence(vector<pSentence>& sentences);

int main()
{
    cout << "Hello, World" << endl;
    string input;
    
    // Vector representing sentences (separated by ;)
    vector<pSentence> sentences;
    Text text {};
    
    // Create first sentence
    pSentence first { new vector<Token> };
    sentences.push_back(std::move(first));
    text.push_back({});
    
    while(cout << "> ", getline(cin, input))
    {
        for(auto c : input)
        {
            // Get the first set of tokens
            Sentence& tokens = *(sentences.back());
            
            // Skip
            if     (c == ' ' ) continue;
            else if(c == '\t') continue;
            else if(c == '\v') continue;
            else if(c == '\n') continue;
            else if(c == EOL)
            {
                pSentence nouveau { new vector<Token> };
                sentences.push_back(std::move(nouveau));
                for(Token t : tokens)
                    cout << t << endl;
            }
            else if(c >= '0' && c <= '9')
            {
                if(tokens.empty() 
                || tokens.back().type != Type::NUMBER)
                    tokens.push_back({Type::NUMBER, 0});
                
                Token& t = tokens.back();
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
                        sentences.pop_back();
                        pSentence nouveau { new vector<Token> };
                        sentences.push_back(std::move(nouveau));
                        continue;
                }
                tokens.push_back({ Type::OPERATOR, op });
            }
        }
    }
    
    // Take out last (and useless) sentence
    sentences.pop_back();
    
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
    infix_to_posfix (sentences);
    // print_sentence  (sentences);
    
    Prog prog { posfix_to_asm(sentences) };
    cout << prog << endl;
    
    return 0;
}

void infix_to_posfix(vector<pSentence>& sentences)
{
    int i = 0;
    
    stack<char,vector<char>> operators {};
    
    for(pSentence& ptokens : sentences)
    {
        cout << YELLOW << "Sentence " << RESTORE << ++i << endl;
        Sentence posfix;
        for(Token& t : *ptokens)
        {
            switch(t.type)
            {
                case Type::NUMBER:
                    posfix.push_back(t);
                    break;
                
                case Type::OPERATOR:
                    char op;
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
                                    posfix.push_back({Type::OPERATOR, op});
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
                                    posfix.push_back({Type::OPERATOR, op});
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
                                    posfix.push_back({Type::OPERATOR, op});
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
            posfix.push_back({Type::OPERATOR, operators.top()});
            operators.pop();
        }
        
        *ptokens = std::move(posfix);
    }
}

Prog posfix_to_asm(vector<pSentence>& sentences)
{
    Prog prog {};
    
    for(pSentence& ptokens : sentences)
        for(Token& t : *ptokens)
            switch(t.type)
            {
                case Type::NUMBER:
                    prog.push_back({ "PUSH", std::to_string(t.n) });
                    break;
                
                case Type::OPERATOR:
                    prog.push_back({ assembly_symbol_table[t.o] });
                    break;
            }
    
    return prog;
}
           
inline void print_sentence(vector<pSentence>& sentences)
{
    for(pSentence& ptokens : sentences)
        for(Token& t : *ptokens)
            cout << "    " << t << endl;
}
