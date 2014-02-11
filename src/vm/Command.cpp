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

// Default libraries
#include <string>
#include <iomanip>
#include <iostream>

// Libraries
#include "Colors.hpp"
#include "Number.hpp"
#include "Command.hpp"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                Command                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream& vm::operator<<(std::ostream& os, const Command& cmd)
{
    os << "[";
    (cmd.cmd != "") ? os << cmd.cmd : os << "none";
    os << ",";
    (cmd.arg)       ? os << cmd.arg->to_string() : os << "";
    os << ",";
    (cmd.lab != "") ? os << cmd.lab : os << "none";
    os << "]";
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  PROG                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream& vm::operator<<(std::ostream& os, const Prog& prog)
{
    unsigned int max_cmd = 0, max_arg = 0, max_lab = 0;
    for(const Command& cmd : prog)
    {
        if(cmd.cmd.size() > max_cmd) max_cmd = cmd.cmd.size();
        if(cmd.arg && cmd.arg->to_string().size() > max_arg) 
            max_arg = cmd.arg->to_string().size();
        if(cmd.lab.size() > max_lab) max_lab = cmd.lab.size();
    }
    
    bool first = true;
    for(const Command& cmd : prog)
    {
        // Jump line
        (first) ? first = false : os << std::endl;
        
        // Label
        if(max_lab != 0) os << std::setw(max_lab+2);
        (cmd.lab != "") 
            ? os << std::left << BLUE << (cmd.lab + ": ") 
            : os << RESTORE << "";
        
        // Command
        os << std::setw(max_cmd) << std::left 
           << YELLOW << cmd.cmd << RESTORE;
        
        // Argument
        os << " ";
        os << std::setw(max_arg) << std::left 
           << PURPLE << ((cmd.arg) ? cmd.arg->to_string() : "") 
           << RESTORE;
    }
    
    return os;
}
