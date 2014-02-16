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
#include "Bool.hpp"
#include "Number.hpp"
#include "Address.hpp"
#include "Stackable.hpp"
using namespace vm;

template<typename Func>
void Asm::JCMP(
    const RVM& rvm, 
    const stk::Stackable_ptr& stk, 
    Func cmp)
{
    bool result;
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
    
    int index = static_cast<int>(dynamic_cast<stk::Address*>(stk.get())->get());
    if(cmp(result, true)) rvm.PC = index-1;
}

void Asm::JMP(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return true; });
}

void Asm::JIT(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return result == b; });
}

void Asm::JIF(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
{
    JCMP(rvm, stk, [] (bool result, bool b) { return result != b; });
}
