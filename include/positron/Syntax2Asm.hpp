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
                                                      
#ifndef HPP_POSITRON_SYNTAX2ASM_DEFINED
#define HPP_POSITRON_SYNTAX2ASM_DEFINED

// Default libraries
#include <string>

// Libraries
#include "Text.hpp"
#include "Number.hpp"
#include "Command.hpp"
#include "Syntax_C.hpp"

namespace positron
{
    class Syntax2Asm : public Visitor
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
                if(exprC == nullptr) return;
                stk::Number num {
                    dynamic_cast<const numC *>(exprC)->get()
                };
                prog.push_back(vm::Command 
                    { vm::Command::Opcode::PUSH, num });
            }
            
            void visit(const idC *exprC) const 
            {
                if(exprC == nullptr) return;
                stk::Text num {
                    dynamic_cast<const idC *>(exprC)->get()
                };
                // TODO: Implement idC
                // prog.push_back(vm::Command 
                    // { vm::Command::Opcode::PUSH, num });
            }
            
            void visit(const lamC *exprC) const 
            {
                if(exprC == nullptr) return;
                // TODO: Implement lamC
            }
            
            void visit(const plusC *exprC) const 
            {
                if(exprC == nullptr) return;
                exprC->accept_l(*this); 
                exprC->accept_r(*this);
                prog.push_back(vm::Command 
                    { vm::Command::Opcode::ADD });
            }
            
            void visit(const bminusC *exprC) const 
            {
                if(exprC == nullptr) return;
                exprC->accept_l(*this); 
                exprC->accept_r(*this);
                prog.push_back(vm::Command 
                    { vm::Command::Opcode::SUB });
            }
            
            void visit(const multC *exprC) const 
            {
                if(exprC == nullptr) return;
                exprC->accept_l(*this); 
                exprC->accept_r(*this);
                prog.push_back(vm::Command {
                    vm::Command::Opcode::MUL });
            }
            
            void visit(const divC *exprC) const 
            {
                if(exprC == nullptr) return;
                exprC->accept_l(*this); 
                exprC->accept_r(*this);
                prog.push_back(vm::Command {
                    vm::Command::Opcode::DIV });
            }
            
            void visit(const ifC *exprC) const 
            {
                if(exprC == nullptr) return;
                
                // Create tags for jumps
                int lvl = c_if; c_if++;
                std::string s_if    { "IF"    + std::to_string(lvl) };
                std::string s_else  { "ELSE"  + std::to_string(lvl) };
                std::string s_endif { "ENDIF" + std::to_string(lvl) };
                
                // Calculate condition
                exprC->accept_l(*this); 
                
                // Test condition
                prog.push_back(vm::Command {
                    vm::Command::Opcode::PUSH, stk::Number{1} });
                prog.push_back(vm::Command {
                    vm::Command::Opcode::EQ });
                prog.push_back(vm::Command {
                    vm::Command::Opcode::JIT, stk::Text{s_if} });
                prog.push_back(vm::Command {
                    vm::Command::Opcode::JMP, stk::Text{s_else} });
                
                // Condition if true
                prog.push_back(vm::Command { s_if });
                exprC->accept_r(*this);
                prog.push_back(vm::Command {
                    vm::Command::Opcode::JMP, stk::Text{s_endif} });
                
                // Condition if false
                prog.push_back(vm::Command { s_else });
                exprC->accept_x(*this);
                prog.push_back(vm::Command { s_endif });
            }
            
            void visit(const appC *exprC) const 
            {
                if(exprC == nullptr) return;
                // TODO: Implement appC
            }
    };
}

#endif
