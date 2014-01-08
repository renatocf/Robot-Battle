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

#ifndef HPP_COMMAND_DEFINED
#define HPP_COMMAND_DEFINED

// Default libraries
#include <string>
#include <vector>

class Command
{
    public:
        const std::string com; // command
        const std::string arg; // argument
        const std::string lab; // label
        
        Command()
            : com{""}, arg{""}, lab{""} {}
        Command(std::string com)
            : com{com}, arg{""}, lab{""} {}
        Command(std::string com, std::string arg)
            : com{com}, arg{arg}, lab{""} {}
        Command(std::string com, std::string arg, std::string lab)
            : com{com}, arg{arg}, lab{lab} {}
        
        friend std::ostream &operator<<(std::ostream &os, const Command& com);
};

using Prog = std::vector<Command>;
std::ostream &operator<<(std::ostream &os, const Prog& prog);

#endif
