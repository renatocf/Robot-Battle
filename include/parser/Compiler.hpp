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

#ifndef HPP_PARSER_COMPILER_DEFINED
#define HPP_PARSER_COMPILER_DEFINED

// Default libraries
#include <memory>

// Libraries
#include "Number.hpp"
#include "Command.hpp"
#include "Syntax_C.hpp"
#include "Stackable.hpp"

#include <iostream>
using namespace std;

namespace parser
{
    class Compiler
    {
        public:
            vm::Prog 
            compile(const ExprC& root)
            {
                vm::Prog prog {};
                prog = std::move(compileR(root, prog));
                prog.push_back(vm::Command { vm::Command::Opcode::PRN });
                prog.push_back(vm::Command { vm::Command::Opcode::END });
                return prog;
            }
            
        private:
            vm::Prog compileR(const ExprC& root, vm::Prog& prog)
            {
                switch(root.type)
                {
                    case ExprC::Type::plusC:
                        for(const ExprC *arg : root.get())
                            compileR(*arg, prog);
                        prog.push_back(vm::Command { 
                            vm::Command::Opcode::ADD });
                        break;
                        
                    case ExprC::Type::multC:
                        for(const ExprC *arg : root.get())
                            compileR(*arg, prog);
                        prog.push_back(vm::Command {
                            vm::Command::Opcode::MUL });
                        break;
                    
                    case ExprC::Type::numC:
                        stk::Stackable_ptr num { new stk::Number {
                            dynamic_cast<const numC&>(root).get_content()
                        }};
                        prog.push_back(vm::Command {
                            vm::Command::Opcode::PUSH, num });
                        break;
                }
                return prog;
            }
    };
}

#endif
