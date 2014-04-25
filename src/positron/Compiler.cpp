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
                                                      
// Libraries                                          
#include "Compiler.hpp"                         
using namespace positron;

void Compiler::visit(const intC *exprC) const
{
    if(exprC == nullptr) return;
    stk::Int num {
        dynamic_cast<const intC *>(exprC)->get()
    };
    prog.push_back(vm::Command 
        { vm::Command::Opcode::PUSH, num });
}

void Compiler::visit(const floatC *exprC) const
{
    if(exprC == nullptr) return;
    stk::Float num {
        dynamic_cast<const floatC *>(exprC)->get()
    };
    prog.push_back(vm::Command 
        { vm::Command::Opcode::PUSH, num });
}

void Compiler::visit(const varC *exprC) const
{
    if(exprC == nullptr) return;
    stk::Text id {
        dynamic_cast<const varC *>(exprC)->get()
    };
    // TODO: Implement varC
    // prog.push_back(vm::Command 
        // { vm::Command::Opcode::PUSH, num });
}

void Compiler::visit(const stringC *exprC) const
{
    if(exprC == nullptr) return;
    stk::Text str {
        dynamic_cast<const stringC *>(exprC)->get()
    };
    prog.push_back(vm::Command 
        { vm::Command::Opcode::PUSH, str });
}

void Compiler::visit(const lamC *exprC) const
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::STO, stk::Int{10} });
    exprC->accept_r(*this);
    
    // TODO: Implement lamC
}
            
void Compiler::visit(const plusC *exprC) const
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::ADD });
}

void Compiler::visit(const bminusC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::SUB });
}

void Compiler::visit(const multC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::MUL });
}

void Compiler::visit(const divC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::DIV });
}

void Compiler::visit(const modC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::MOD });
}
            
void Compiler::visit(const eqC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::EQ });
}

void Compiler::visit(const neC *exprC) const
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::NE });
}

void Compiler::visit(const ltC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::LT });
}

void Compiler::visit(const leC *exprC) const 
{
if(exprC == nullptr) return;
exprC->accept_l(*this); 
exprC->accept_r(*this);
prog.push_back(vm::Command
    { vm::Command::Opcode::LE });
}

void Compiler::visit(const gtC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::GT });
}

void Compiler::visit(const geC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
    prog.push_back(vm::Command
        { vm::Command::Opcode::GE });
}

void Compiler::visit(const ifC *exprC) const 
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
        vm::Command::Opcode::PUSH, stk::Int{0} });
    prog.push_back(vm::Command {
        vm::Command::Opcode::EQ });
    prog.push_back(vm::Command {
        vm::Command::Opcode::JIT, stk::Text{s_else} });
    
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
            
void Compiler::visit(const seqC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    exprC->accept_r(*this);
}

void Compiler::visit(const appC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_r(*this); // Argument
    exprC->accept_l(*this); // Body
    // TODO: Implement appC
}
            
void Compiler::visit(const setC *exprC) const 
{
    if(exprC == nullptr) return;
}

void Compiler::visit(const storeC *exprC) const 
{
    if(exprC == nullptr) return;
}

void Compiler::visit(const fetchC *exprC) const 
{
    if(exprC == nullptr) return;
}

void Compiler::visit(const printC *exprC) const 
{
    if(exprC == nullptr) return;
    exprC->accept_l(*this); 
    prog.push_back(vm::Command {
        vm::Command::Opcode::PRN });
}
