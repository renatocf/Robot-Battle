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
#include "Ctrl.hpp"
#include "Stk.hpp"
#include "Arit.hpp"
using namespace vm;

void vm::ctrl(const RVM& rvm, const Command& cmd)
{
    switch(cmd.cmd)
    {
        // Stack functions
        case Command::Opcode::PUSH: vm::PUSH (rvm, cmd.arg); break;
        case Command::Opcode::POP:  vm::POP  (rvm);          break;
        case Command::Opcode::SWAP: vm::SWAP (rvm);          break;
        case Command::Opcode::DUP:  vm::DUP  (rvm);          break;
        
        // Arithmetic functions
        case Command::Opcode::ADD:  vm::ADD  (rvm);          break;
        case Command::Opcode::SUB:  vm::SUB  (rvm);          break;
        case Command::Opcode::DIV:  vm::DIV  (rvm);          break;
        case Command::Opcode::MUL:  vm::MUL  (rvm);          break;
        case Command::Opcode::MOD:  vm::MOD  (rvm);          break;
        
        // Control functions
        case Command::Opcode::END:  
            break;
        default: 
            break;
    }
}
