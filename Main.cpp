// Default libraries
#include <memory>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Libraries
#include "Token.hpp"
#include "Colors.hpp"

static const char EOL = ';';

// Sentence and poiter to it
using sentence_t  = vector<Token>;
using psentence_t = unique_ptr<vector<Token>>;

void infix_to_posfix(vector<psentence_t>& sentences);

class Sentence
{
    // using sentence_t  = vector<Token>;
    // using psentence_t = unique_ptr<vector<Token>>;
    
    private:
        vector<psentence_t> sentences;
    public:
        Sentence() {}
        Sentence(std::initializer_list<sentence_t> list) 
        {
            for(sentence_t sentence : list)
            {
                psentence_t aux { &sentence };
                sentences.push_back(std::move(aux));
            }
        }
        
        void push_back()
        {
            psentence_t aux { new sentence_t };
            sentences.push_back(std::move(aux));
        }
        
        void push_back(sentence_t s)
        {
            psentence_t aux { &s };
            sentences.push_back(std::move(aux));
        }
        
        sentence_t pop_back()
        {
            sentence_t aux { std::move(*(sentences.back())) };
            sentences.pop_back();
            return aux;
        }
        
        const std::vector<psentence_t>::iterator begin() const { return sentences.begin(); }
        const std::vector<psentence_t>::iterator end  () const { return sentences.end();   }
};

int main()
{
    cout << "Hello, World" << endl;
    string input;
    
    // Vector representing sentences (separated by ;)
    vector<psentence_t> sentences;
    
    // Create first sentence
    psentence_t first { new vector<Token> };
    sentences.push_back(std::move(first));
    
    while(cout << "> ", getline(cin, input))
    {
        for(auto c : input)
        {
            // Get the first set of tokens
            sentence_t& tokens = *(sentences.back());
            
            // Skip
            if     (c == ' ' ) continue;
            else if(c == '\t') continue;
            else if(c == '\v') continue;
            else if(c == '\n') continue;
            else if(c == EOL)
            {
                psentence_t nouveau { new vector<Token> };
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
                        psentence_t nouveau { new vector<Token> };
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
    infix_to_posfix(sentences);
    
    return 0;
}

void infix_to_posfix(vector<psentence_t>& sentences)
{
    int i = 0;
    for(psentence_t& ptokens : sentences)
    {
        cout << YELLOW << "Sentence " << RESTORE << ++i << endl;
        for(Token& t : *ptokens)
            cout << "    " << t << endl;
    }
}
