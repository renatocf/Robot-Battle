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

#ifndef HPP_VM_STK_DEFINED
#define HPP_VM_STK_DEFINED

// Libraries
#include "RVM.hpp"
#include "Debug.hpp"
#include "Stackable.hpp"

namespace vm
{
    inline void 
    push(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
    {
        rvm.DATA.push_back(stk::Stackable_ptr { stk->clone() });
    }
    
    inline stk::Stackable_ptr
    pop(const vm::RVM& rvm)
    {
        stk::Stackable_ptr ret { std::move(rvm.DATA.back()) };
        rvm.DATA.pop_back();
        return ret;
    }
    
    inline void 
    PUSH(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
    {
        vm::push(rvm, stk); Debug::printStack(rvm);
    }
    
    inline stk::Stackable_ptr
    POP(const vm::RVM& rvm)
    {
        stk::Stackable_ptr aux { pop(rvm) };
        Debug::printStack(rvm);
        return aux;
    }
    
    inline void
    SWAP(const vm::RVM& rvm)
    {
        stk::Stackable_ptr first  { pop(rvm) };
        stk::Stackable_ptr second { pop(rvm) };
        push(rvm, second); push(rvm, first);
        Debug::printStack(rvm);
    }
    
    inline void
    DUP(const vm::RVM& rvm)
    {
        stk::Stackable_ptr aux { pop(rvm) };
        stk::Stackable_ptr nouveau { aux->clone() };
        push(rvm, aux); push(rvm, nouveau);
        Debug::printStack(rvm);
    }
}

#endif
