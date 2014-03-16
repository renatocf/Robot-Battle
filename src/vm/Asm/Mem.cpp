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
 * @file  Mem.cpp
 * @brief Provide assembly RAM operations for a RVM.
 */

// Libraries
#include "Asm.hpp"
#include "Debug.hpp"
#include "Address.hpp"
using namespace vm;

/**
 * Assembly function STO. <br>
 * Remove the top most argument of the main stack of a RVM and 
 * stores it in the position specified by a numeric argument.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::STO(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    int pos = dynamic_cast<stk::Address*>(stk.get())->get();
    rvm.RAM[pos] = stk::Stackable_ptr { Asm::pop(rvm) };
    Debug::printRAM(rvm);
}

/**
 * Assembly function RCL. <br>
 * Remove the RAM stackable specified by a numerical argument
 * and pushes it in the main stack of its RVM.
 * @param rvm Robot Virtual Machine
 * @param stk Reference to pointer to stackable
 */
void Asm::RCL(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    int pos = dynamic_cast<stk::Address*>(stk.get())->get();
    Asm::push(rvm, rvm.RAM[pos]);
    rvm.RAM.erase(pos);
    Debug::printRAM(rvm);
    Debug::printStack(rvm);
}
