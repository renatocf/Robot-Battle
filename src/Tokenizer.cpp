/**********************************************************************/
/* Copyright 2014 RCF                                                 */ 
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in compliance with the License.   */
/* You may obtain a copy of the License at                            */
/*                                                                    */
/*     http://www.apache.org/licenses/LICENSE-2.0                     */
/*                                                                    */
/* Unless required by applicable law or agreed to in writing,         */
/* software distributed under the License is distributed on an        */
/* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,       */
/* either express or implied.                                         */
/* See the License for the specific language governing permissions    */
/* and limitations under the License.                                 */
/**********************************************************************/

// Default libraries
#include <string>
#include <iostream>

// Libraries
#include "Token.hpp"
#include "Tokenizer.hpp"

// Macros
static const char EOL = ';';

bool tokenize(std::istream& is, Text &text)
{
    std::string input;
    if(!std::getline(is, input)) return false;
    
    // IO Errors
    if(is.bad()) 
    {
        std::cerr << "[TOKENIZER] IO error" << std::endl;
        return false;
    }
    
    // Needs a non-empty text to start.
    // If there is a sentence, uses it as context
    if(text.empty()) text.push_back(Sentence{});
    
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
                    std::cerr << "Unidentified token \"" << c << "\"" << std::endl;
                    text.pop_back();
                    text.push_back(Sentence{});
                    continue;
            }
            sentence.push_back(Token { Type::OPERATOR, op });
        }
    }
    
    return true;
}
