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
#include <memory>
#include <iostream>
using namespace std;

// Libraries
#include "Token.hpp"
#include "Parser.hpp"
#include "Command.hpp"
#include "Grammar.hpp"
#include "Tokenizer.hpp"
#include "RVM.hpp"
#include "Number.hpp"
#include "Stackable.hpp"
#include "Quark.hpp"

static const char EOL = ';';

vm::Prog posfix_to_asm(Text& sentences);

int main(int argc, char **argv)
{
    // Usage
    if(argc != 2)
    {
        cout << "USAGE: Main program_name.asm" << endl;
        return 0;
    }
    
    parser::quark::Func_ptr upload = parser::quark::functions[argv[1]];
    cout << upload() << endl;
    
    vm::RVM Bender { upload() };
    Bender.run();
    
    // Parser parser {};
    // Text text { parser.parse() };
    // 
    // vm::Prog prog   { posfix_to_asm(text) };
    // vm::RVM  Bender { prog };
    // Bender.run();
    
    return 0;
}

vm::Prog posfix_to_asm(Text& text)
{
    vm::Prog prog {};
    
    for(Sentence& sentence : text)
    {
        for(Token& t : sentence)
            switch(t.type)
            {
                case Type::NUMBER:
                    prog.push_back(
                        vm::Command { vm::Command::Opcode::PUSH, 
                            stk::Stackable_ptr{new stk::Number{t.n}} }
                    );
                    break;
                
                case Type::OPERATOR:
                    prog.push_back(
                        vm::Command { assembly_symbol_table[t.o] });
                    break;
                
                case Type::UNDEFINED:
                    cerr << "[POSFIX_TO_ASM] This should not happen" << endl;
                    break;
            }
        prog.push_back(vm::Command { vm::Command::Opcode::POP });
    }
    
    prog.push_back(vm::Command { vm::Command::Opcode::END });
    
    return prog;
}
