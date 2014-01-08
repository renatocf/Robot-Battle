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
#include <iostream>
using namespace std;

// Libraries
#include "Token.hpp"
#include "Parser.hpp"
#include "Command.hpp"
#include "Tokenizer.hpp"
#include "Grammar.hpp"

static const char EOL = ';';

Prog posfix_to_asm(Text& sentences);

int main()
{
    cout << "Hello, World" << endl;
    
    Parser parser {};
    Text text { parser.parse() };
    
    // Vector representing sentences (separated by ;)
    // Text text {};
    // 
    // while(cout << "> ", tokenize(cin, text));
    // 
    // // Take out last (and useless) sentence
    // text.pop_back();
    // 
    // cout << endl;
    
    Prog prog { posfix_to_asm(text) };
    cout << prog << endl;
    
    return 0;
}

Prog posfix_to_asm(Text& text)
{
    Prog prog {};
    
    for(Sentence& sentence : text)
    {
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
        prog.push_back(Command { "POP" });
    }
    
    prog.push_back(Command { "END" });
    
    return prog;
}
