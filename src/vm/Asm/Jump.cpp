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
 * @file   Jump.cpp
 * @brief  Provide assembly jumps for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Asm.hpp"
#include "Bool.hpp"
#include "Text.hpp"
#include "Number.hpp"
#include "Address.hpp"
#include "Stackable.hpp"
using namespace vm;

/**
 * Assembly auxiliar function JCMP. <br>
 * Given a comparison function, jump to the PC of a RVM to the position 
 * of a stackable given as argument iff the condition is true.
 * @param rvm Robot Virtual Machine
 * @param cmp Boolean function to be tested in the top most stackable
 *            of the main stack of a RVM
 */
template<typename Func>
void Asm::JCMP(
    const RVM& rvm, 
    const stk::Stackable_ptr& stk, 
    Func cmp, 
    bool pop)
{
    bool result = true;
    if(pop)
    {
        stk::Stackable_ptr b { Asm::pop(rvm) };
        
        if(b->type == stk::Stackable::Type::Bool)
        {
            result = dynamic_cast<stk::Bool*>(b.get())->get();
        }
        else if(b->type == stk::Stackable::Type::Number)
        {
            result = (dynamic_cast<stk::Number*>(b.get())->get() != 0)
                ? true : false;
        }
        else { result = false; /* TODO: put error */ }
    }
    
    int index = -1;
    if(stk->type == stk::Stackable::Type::Address)
        index = static_cast<int>(
            dynamic_cast<stk::Address*>(stk.get())->get()
        );
    else if(stk->type == stk::Stackable::Type::Text)
        index = static_cast<int>(
            rvm.LABEL[dynamic_cast<stk::Text*>(stk.get())->get()]
        );
    else { result = false; /* TODO: put error */ }
    
    if(cmp(result, true)) rvm.PC = index-1;
}

/**
 * Assembly function JMP. <br>
 * Unconditionally jump the PC of a RVM to the position specified
 * by a stackable given as argument.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::JMP(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return true; }, false);
}

/**
 * Assembly function JIT. <br>
 * If the top most stackable of a RVM is either a true boolean or a 
 * non-zero number, jump the PC to the position specified by a 
 * stackable given as argument.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::JIT(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return result == b; });
}

/**
 * Assembly function JIF. <br>
 * If the top most stackable of a RVM is either a false boolean or zero,
 * jump the PC to the position of a stackable given as argument.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::JIF(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return result != b; });
}
