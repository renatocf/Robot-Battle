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
#include <stack>
#include <vector>
#include <iostream>
#include <unordered_map>

// Internal libraries
#include "State.hpp"
#include "Command.hpp"
#include "Stackable.hpp"

namespace vm
{
    class RVM
    {
        private:
            // Execution memory
            std::vector        <Command>         PROG  {};
            std::unordered_map <std::string,int> LABEL {};
            
            // Internal-use memory
            mutable std::stack         <int>                    CTRL  {};
            mutable std::stack         <stk::Stackable>         DATA  {};
            mutable std::unordered_map <int,stk::Stackable_ptr> RAM   {};
            
            mutable bool syscall   { false };
            mutable State activity { State::ACTIVE };
            
        public:
            RVM(std::vector<Command> PROG)
            {
                upload(PROG);
            }
            
            void upload(std::vector<Command> PROG)
            {
                this->PROG = std::move(PROG); //upload_labels();
            }
            
            void exec() const;
            void run()  const;
            
            friend std::ostream& 
            operator<<(std::ostream& os, const RVM& rvm)
            {
                os << rvm.PROG; return os;
            }
    };
}

#endif
