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

#ifndef HPP_VM_Command_DEFINED
#define HPP_VM_Command_DEFINED

// Default libraries
#include <string>
#include <vector>
#include <memory>

// Internal libraries
#include "Stackable.hpp"

namespace vm 
{
    class Command
    {
        public:
            const std::string cmd        {}; // Command
            const stk::Stackable_ptr arg {}; // argument
            const std::string lab        {}; // label
            
            Command(
                std::string cmd        = {}, 
                stk::Stackable_ptr arg = {}, 
                std::string lab        = {}
            )
                : cmd{cmd}, arg{std::move(arg)}, lab{lab} {}
            
            Command(const Command& cmd)
                : cmd{cmd.cmd}, 
                  arg{cmd.arg ? cmd.arg->clone() : nullptr},
                  lab{cmd.lab} {}
            
            // Command(const Command&& cmd)
                // : cmd{cmd.cmd}, arg{cmd.arg->clone()}, lab{cmd.lab} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const Command& cmd);
    };
    
    std::ostream& operator<<(std::ostream& os, const Command& cmd);
}

namespace vm
{
    using Prog = std::vector<Command>;
    std::ostream &operator<<(std::ostream &os, const Prog& prog);
}

#endif
