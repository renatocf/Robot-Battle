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

// Default libraries
#include <string>
#include <iomanip>
#include <iostream>

// Libraries
#include "Colors.hpp"
#include "Command.hpp"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                COMMAND                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream &operator<<(std::ostream &os, const Command& com)
{
    os << "[";
    (com.com != "") ? os << com.com : os << "none";
    os << ",";
    (com.arg != "") ? os << com.arg : os << "none";
    os << ",";
    (com.lab != "") ? os << com.lab : os << "none";
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
std::ostream &operator<<(std::ostream &os, const Prog& prog)
{
    unsigned int max_com = 0, max_arg = 0, max_lab = 0;
    for(Command cmd : prog)
    {
        if(cmd.com.size() > max_com) max_com = cmd.com.size();
        if(cmd.arg.size() > max_arg) max_arg = cmd.arg.size();
        if(cmd.lab.size() > max_lab) max_lab = cmd.lab.size();
    }
    
    bool first = true;
    for(Command cmd : prog)
    {
        // Jump line
        (first) ? first = false : os << std::endl;
        
        // Label
        if(max_lab != 0) os << std::setw(max_lab+2);
        (cmd.lab != "") ? os << std::left << BLUE << (cmd.lab + ": ") : os << RESTORE << "";
        
        // Command
        os << std::setw(max_com) << std::left << YELLOW << cmd.com << RESTORE;
        
        // Argument
        os << " ";
        os << std::setw(max_arg) << std::left << PURPLE << cmd.arg << RESTORE;
    }
    
    return os;
}
