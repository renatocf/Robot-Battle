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
#include <iostream>

// Internal libraries
#include "Debug.hpp"
#include "Colors.hpp"
using namespace vm;

void vm::Debug::printStack(const RVM& rvm)
{
    std::cout << RED << "[STACK]" << RESTORE << std::endl;
    std::cout << "    ";
    for(stk::Stackable_ptr& p : rvm.DATA)
        std::cout << PURPLE << p << RESTORE << ", ";
    
    std::cout << RED << "[TOP]" << RESTORE << std::endl;
}

void vm::Debug::printCommand(const RVM& rvm, int pos)
{
    using namespace std;
    cout << YELLOW << pos << " ";
    cout << YELLOW << rvm.PROG[pos].cmd << RESTORE << " ";
    cout << PURPLE << rvm.PROG[pos].arg << RESTORE << endl;
}
