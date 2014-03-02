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

// Internal libraries
#include "Debug.hpp"
#include "Colors.hpp"
using namespace vm;

// Class variable initialization
bool Debug::OFF { true };

void vm::Debug::printRAM(const RVM& rvm)
{
    // Do nothing when debugging is off
    if(Debug::OFF) return;
    
    std::cout << BLUE << "[RAM]" << RESTORE << std::endl;
    
    int count = 0;
    bool first = true;
    for(auto& dat : rvm.RAM)
    {
        for(; count < dat.first; ++count)
        {
            std::cout << BLUE << (first ? "    [ #" : " | #");
            first = false;
        }
        std::cout << BLUE << (first ? "    [ " : " | ") 
                  << PURPLE << dat.second << RESTORE;
        first = false; 
        ++count;
    }
    
    std::cout << BLUE << " ]" << RESTORE << std::endl;
}

void vm::Debug::printStack(const RVM& rvm)
{
    // Do nothing when debugging is off
    if(Debug::OFF) return;
    
    std::cout << RED << "[STACK]" << RESTORE << std::endl;
    std::cout << "    ";
    for(stk::Stackable_ptr& p : rvm.DATA)
        std::cout << PURPLE << p << RESTORE << ", ";
    
    std::cout << RED << "[TOP]" << RESTORE << std::endl;
}

void vm::Debug::printCommand(const RVM& rvm, int pos)
{
    // Do nothing when debugging is off
    if(Debug::OFF) return;
    
    // Auxiliar var for ptinting
    const Command& cmd = rvm.PROG[pos];
    
    // Line:
    std::cout << YELLOW << std::right 
         << std::setw(rvm.max_lin) << pos;
    
    // Command
    std::cout << " ";
    std::cout << YELLOW << std::left << std::setw(rvm.max_cmd) 
       << cmd.cmd << RESTORE;
    
    // Argument
    std::cout << " ";
    std::cout << PURPLE << std::left << std::setw(rvm.max_arg) 
       << ((cmd.arg) ? cmd.arg->to_string() : "") 
       << RESTORE;
    
    std::cout << std::endl;
}
