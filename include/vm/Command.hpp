/**********************************************************************/
/* Copyright 2014 RCF                                                 */ 
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in cmdpliance with the License.   */
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

#ifndef HPP_VM_COMMAND_DEFINED
#define HPP_VM_COMMAND_DEFINED

// Default libraries
#include <string>
#include <vector>
#include <memory>

// Libraries
#include "stk.hpp"

namespace vm 
{
    class Command
    {
        public:
            enum class Opcode
            {
                NONE = 0,                     // Default value
                PRN ,                         // IO commands
                PUSH, POP , SWAP, DUP ,       // Stack commands
                ADD , SUB , DIV , MUL , MOD , // Arithmetic commands
                STO , RCL ,                   // Memory functions
                EQ  , NE  , NIL ,             // Test functions
                GT  , GE  , LT  , LE,         // 
                JMP , JIT , JIF ,             // Jumps commands
                NOP , END ,                   // Workflow commands
                CALL, RET ,                   // Functions commands
                DRAG, DROP, HIT ,             // Syscall commands
                LOOK, SEE , ASK ,             // 
                ITEM, SEEK,                   // Item commands
                ALOC, FREE, GET, SET,         // Local var commands
                READ, WRT , SEND,             // Network commands
                COOR, GTIJ                    // Type cast
            };
    
            const Opcode             cmd {}; // Command
            const stk::Stackable_ptr arg {}; // argument
            const std::string        lab {}; // label
            
            Command(const vm::Command::Opcode& cmd)
                : cmd{cmd} {}
            
            Command(const std::string& lab)
                : lab{lab} {}
            
            Command(
                const vm::Command::Opcode& cmd, 
                const std::string& lab)
                : cmd{cmd}, lab{lab} {}
            
            Command(
                const vm::Command::Opcode& cmd, 
                const stk::Stackable&      arg,
                const std::string&         lab = {}
            )
                : cmd{cmd}, arg{arg.clone()}, lab{lab} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const Command& cmd);
    };
    
    std::ostream& operator<<(std::ostream& os, const Command& cmd);
    
    // Opcode
    std::string   to_string(const Command::Opcode& op);
    std::ostream& operator<<(std::ostream& os, const Command::Opcode& op);
}

namespace vm
{
    using Prog = std::vector<Command>;
    std::ostream& operator<<(std::ostream& os, const Prog& prog);
}

#endif
