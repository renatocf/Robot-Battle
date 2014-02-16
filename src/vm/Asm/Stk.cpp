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

// Libraries
#include "Asm.hpp"
#include "Debug.hpp"
using namespace vm;

void Asm::push(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    rvm.DATA.push_back(stk::Stackable_ptr { stk->clone() });
}

stk::Stackable_ptr Asm::pop(const vm::RVM& rvm)
{
    stk::Stackable_ptr ret { std::move(rvm.DATA.back()) };
    rvm.DATA.pop_back();
    return ret;
}

void Asm::PUSH(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    Asm::push(rvm, stk); Debug::printStack(rvm);
}

void Asm::POP(const vm::RVM& rvm)
{
    Asm::pop(rvm); Debug::printStack(rvm);
}

void Asm::SWAP(const vm::RVM& rvm)
{
    stk::Stackable_ptr first  { Asm::pop(rvm) };
    stk::Stackable_ptr second { Asm::pop(rvm) };
    Asm::push(rvm, second);
    Asm::push(rvm, first);
    Debug::printStack(rvm);
}

void Asm::DUP(const vm::RVM& rvm)
{
    stk::Stackable_ptr aux     { Asm::pop(rvm) };
    stk::Stackable_ptr nouveau { aux->clone() };
    Asm::push(rvm, aux); 
    Asm::push(rvm, nouveau);
    Debug::printStack(rvm);
}
