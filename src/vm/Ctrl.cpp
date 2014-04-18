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

// Internal libraries
#include "Asm.hpp"
#include "Ctrl.hpp"
using namespace vm;

void vm::ctrl(const RVM& rvm, const Command& cmd)
{
    switch(cmd.cmd)
    {
        // Stack functions
        case Command::Opcode::PUSH: vm::Asm::PUSH (rvm, cmd.arg); break;
        case Command::Opcode::POP:  vm::Asm::POP  (rvm);          break;
        case Command::Opcode::SWAP: vm::Asm::SWAP (rvm);          break;
        case Command::Opcode::DUP:  vm::Asm::DUP  (rvm);          break;
        
        // Arithmetic functions
        case Command::Opcode::ADD:  vm::Asm::ADD  (rvm);          break;
        case Command::Opcode::SUB:  vm::Asm::SUB  (rvm);          break;
        case Command::Opcode::DIV:  vm::Asm::DIV  (rvm);          break;
        case Command::Opcode::MUL:  vm::Asm::MUL  (rvm);          break;
        case Command::Opcode::MOD:  vm::Asm::MOD  (rvm);          break;
        
        // Memory functions
        case Command::Opcode::STO:  vm::Asm::STO  (rvm, cmd.arg); break;
        case Command::Opcode::RCL:  vm::Asm::RCL  (rvm, cmd.arg); break;
        
        // IO functions
        case Command::Opcode::PRN:  vm::Asm::PRN  (rvm);          break;
        
        // Comparison functions
        case Command::Opcode::EQ:   vm::Asm::EQ   (rvm);          break; 
        case Command::Opcode::NE:   vm::Asm::NE   (rvm);          break; 
        case Command::Opcode::GT:   vm::Asm::GT   (rvm);          break; 
        case Command::Opcode::GE:   vm::Asm::GE   (rvm);          break; 
        case Command::Opcode::LT:   vm::Asm::LT   (rvm);          break; 
        case Command::Opcode::LE:   vm::Asm::LE   (rvm);          break; 
        
        // Jump functions
        case Command::Opcode::JMP:  vm::Asm::JMP  (rvm, cmd.arg); break; 
        case Command::Opcode::JIT:  vm::Asm::JIT  (rvm, cmd.arg); break; 
        case Command::Opcode::JIF:  vm::Asm::JIF  (rvm, cmd.arg); break; 
        
        // Function functions
        case Command::Opcode::CALL: vm::Asm::CALL (rvm, cmd.arg); break; 
        case Command::Opcode::RET:  vm::Asm::RET  (rvm);          break; 
        
        // Halt functions
        case Command::Opcode::NOP:  vm::Asm::NOP  (rvm);          break;
        case Command::Opcode::END:  vm::Asm::END  (rvm);          break;
        
        default:
            break;
    }
}
