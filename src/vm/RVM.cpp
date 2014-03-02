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
#include <iomanip>
#include <iostream>
using namespace std;

// Internal libraries
#include "RVM.hpp"
#include "Ctrl.hpp"
#include "Debug.hpp"

void vm::RVM::exec() const
{
    if(this->PROG[this->PC].cmd != vm::Command::Opcode::NONE)
    {
        Debug::printCommand(*this, this->PC);
        vm::ctrl(*this, this->PROG[this->PC]);
    }
}

void vm::RVM::run()  const
{
    switch(this->activity)
    {
        case State::ACTIVE:
            this->syscall = false;
            while(!this->syscall)
            {
                this->exec(); 
                ++this->PC;
            }
            break;
            
        case State::SLEEP:
            if(this->PC != 0)
                { --this->PC; this->exec(); ++this->PC; }
            
            break;
    }
}

std::ostream& vm::operator<<(std::ostream& os, const RVM& rvm)
{
    os << rvm.PROG; return os;
}
