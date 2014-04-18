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

/** 
 * @file   Func.cpp
 * @brief  Provide assembly function operations for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "stk.hpp"
#include "Asm.hpp"
using namespace vm;

/**
 * Assembly function CALL. <br>
 * Execute an inconditional jump to a label or address, storing the 
 * address of return in the CTRL stack for doing a callback with RET.
 * @param rvm Robot Virtual Machine
 */
void Asm::CALL(const RVM& rvm, const stk::Stackable_ptr& stk)
{
    rvm.CTRL.push(rvm.PC);
    
    if(stk->type == stk::Stackable::Type::Address)
    {
        unsigned int index {
            dynamic_cast<const stk::Address *>(stk.get())->get()
        };
        
        if(index < rvm.PROG.size())
            rvm.PC = index;
        // else TODO: throw exception
    }
    else if(stk->type == stk::Stackable::Type::Text)
    {
        std::string label {
            dynamic_cast<const stk::Text *>(stk.get())->get()
        };
        if(rvm.LABEL.count(label))
            rvm.PC = rvm.LABEL[label];
        // else TODO: throw exception
    }
    // else TODO: throw exception
}

/**
 * Assembly function RET. <br>
 * Pops the top most saved return address to be able to go back 
 * to the function caller.
 * @param rvm Robot Virtual Machine
 */
void Asm::RET(const RVM& rvm)
{
    try { 
        rvm.PC = rvm.CTRL.top();
        rvm.CTRL.pop();
    }
    catch(...)
    {
        // TODO: deal with exception
    }
}
