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
 * @file   Stk.cpp
 * @brief  Provide assembly stack operations for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Asm.hpp"
#include "Debug.hpp"
using namespace vm;

/**
 * Assembly auxiliar function push. <br>
 * Put a copy of the object pointed by a stackable pointer 
 * in the main stack of a RVM.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::push(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    rvm.DATA.push_back(stk::Stackable_ptr { stk->clone() });
}

/**
 * Assembly auxiliar function pop. <br>
 * Remove the top of the main stack of a RVM, and return 
 * a pointer to it.
 * @param  rvm Robot Virtual Machine
 * @return Pointer to the removed top most stackable of a RVM
 */
stk::Stackable_ptr Asm::pop(const vm::RVM& rvm)
{
    stk::Stackable_ptr ret { std::move(rvm.DATA.back()) };
    rvm.DATA.pop_back();
    return ret;
}

/**
 * Assembly function PUSH. <br>
 * Push a copy of the stackable pointed by a stackable pointer
 * in the main stack of a RVM.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::PUSH(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    Asm::push(rvm, stk); Debug::printStack(rvm);
}

/**
 * Assembly function POP. <br>
 * Remove the top most stackable of a RVM.
 * @param rvm Robot Virtual Machine
 */
void Asm::POP(const vm::RVM& rvm)
{
    Asm::pop(rvm); Debug::printStack(rvm);
}

/**
 * Assembly function SWAP. <br>
 * Swap the two top most stackables of a RVM.
 * @param rvm Robot Virtual Machine
 */
void Asm::SWAP(const vm::RVM& rvm)
{
    stk::Stackable_ptr first  { Asm::pop(rvm) };
    stk::Stackable_ptr second { Asm::pop(rvm) };
    Asm::push(rvm, second);
    Asm::push(rvm, first);
    Debug::printStack(rvm);
}

/**
 * Assembly function DUP. <br>
 * Duplicates the top most stackable of a RVM.
 * @param rvm Robot Virtual Machine
 */
void Asm::DUP(const vm::RVM& rvm)
{
    stk::Stackable_ptr aux     { Asm::pop(rvm) };
    stk::Stackable_ptr nouveau { aux->clone() };
    Asm::push(rvm, aux); 
    Asm::push(rvm, nouveau);
    Debug::printStack(rvm);
}
