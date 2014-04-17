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

#ifndef HPP_VM_RVM_DEFINED
#define HPP_VM_RVM_DEFINED

// Default libraries
#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>

// Libraries
#include "stk.hpp"
#include "State.hpp"
#include "Command.hpp"

namespace vm
{
    class RVM
    {
        private:
            mutable unsigned int max_lin = 0, max_cmd = 0, max_arg = 0;
            
            // Execution memory
            mutable std::vector        <Command>                PROG  {};
            mutable std::unordered_map <std::string,int>        LABEL {};
            
            // Internal-use memory
            mutable int                                         PC    {};
            mutable std::stack         <int>                    CTRL  {};
            mutable std::deque         <stk::Stackable_ptr>     DATA  {};
            mutable std::map           <int,stk::Stackable_ptr> RAM   {};
            
            mutable bool syscall   { false };
            mutable State activity { State::ACTIVE };
            
        public:
            RVM(std::vector<Command> PROG)
            {
                upload(PROG);
            }
            
            void upload(std::vector<Command> PROG)
            {
                this->PROG = std::move(PROG); 
                upload_labels();
            }
            
            void exec() const;
            void run()  const;
            
            friend std::ostream& 
            operator<<(std::ostream& os, const RVM& rvm);
            
            friend class Debug;
            friend class Asm;
        
        private:
            void upload_labels()
            {
                // Maximum command and argument size (debug purposes)
                for(const Command& cmd : this->PROG)
                {
                    if(vm::to_string(cmd.cmd).size() > this->max_cmd) 
                        this->max_cmd = vm::to_string(cmd.cmd).size();
                    if(cmd.arg && cmd.arg->to_string().size() > this->max_arg) 
                        this->max_arg = cmd.arg->to_string().size();
                }
                
                // Maximum line size (debug purposes)
                int aux = this->PROG.size(); 
                for(this->max_lin = 1; aux /= 10; this->max_lin++);
                
                // Save label positions
                for(unsigned int i = 0; i < this->PROG.size(); i++)
                    if(this->PROG[i].lab != "")
                        this->LABEL[this->PROG[i].lab] = static_cast<int>(i);
            }
    };
    
    std::ostream& operator<<(std::ostream& os, const RVM& rvm);
}

#endif
