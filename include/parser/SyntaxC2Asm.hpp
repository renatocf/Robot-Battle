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
                                                      
#ifndef HPP_PARSER_SYNTAXC2ASM_DEFINED
#define HPP_PARSER_SYNTAXC2ASM_DEFINED

// Libraries
#include "Bool.hpp"
#include "Number.hpp"
#include "Command.hpp"
#include "Syntax_C.hpp"

namespace parser
{
    class SyntaxC2Asm : public Visitor
    {
        private:
            mutable vm::Prog prog {};
            mutable unsigned int c_if = 0;
            
        public:
            const vm::Prog get() const
            {
                return prog;
            }
            
            void visit(const numC *exprC) const 
            {
                stk::Stackable_ptr num { new stk::Number {
                    dynamic_cast<const numC *>(exprC)->get_content()
                }};
                prog.push_back(vm::Command 
                    { vm::Command::Opcode::PUSH, num });
            }
            
            void visit(const plusC *exprC) const 
            {
                prog.push_back(vm::Command 
                    { vm::Command::Opcode::ADD });
            }
            
            void visit(const multC *exprC) const 
            {
                prog.push_back(vm::Command {
                    vm::Command::Opcode::MUL });
            }
            
            void visit(const ifC *exprC) const 
            {
                stk::Stackable_ptr test { new stk::Bool{true} };
                prog.push_back(vm::Command {
                    vm::Command::Opcode::JIT,  });
                prog.push_back(vm::Command {
                    vm::Command::Opcode::NONE, nullptr, "IF" + c_if });
            }
    };
}

#endif
