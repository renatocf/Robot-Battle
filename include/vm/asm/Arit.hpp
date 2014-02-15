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

#ifndef HPP_VM_ARIT_DEFINED
#define HPP_VM_ARIT_DEFINED

#include "RVM.hpp"
#include "Stk.hpp"
#include "Number.hpp"
#include "Stackable.hpp"

namespace vm
{
    template<typename Func>
    void operate(const RVM& rvm, Func func)
    {
        stk::Stackable_ptr second { vm::pop(rvm) };
        stk::Stackable_ptr first  { vm::pop(rvm) };
        
        stk::Stackable_ptr nouveau { new stk::Number { 
            func(dynamic_cast<stk::Number*>(first.get())->get(), 
                 dynamic_cast<stk::Number*>(second.get())->get()) 
        }};
        vm::push(rvm, std::move(nouveau));
    }

    inline void ADD(const RVM& rvm)
    {
        operate(rvm, [] (long long a, long long b) { return a + b; });
    }

    inline void SUB(const RVM& rvm)
    {
        operate(rvm, [] (long long a, long long b) { return a - b; });
    }

    inline void MUL(const RVM& rvm)
    {
        operate(rvm, [] (long long a, long long b) { return a * b; });
    }

    inline void DIV(const RVM& rvm)
    {
        operate(rvm, [] (long long a, long long b) { return a / b; });
    }

    inline void MOD(const RVM& rvm)
    {
        operate(rvm, [] (long long a, long long b) { return a % b; });
    }
}

#endif
