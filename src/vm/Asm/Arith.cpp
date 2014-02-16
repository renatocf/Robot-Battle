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
#include "Number.hpp"
using namespace vm;

template<typename Func>
void Asm::operate(const RVM& rvm, Func func)
{
    stk::Stackable_ptr second { Asm::pop(rvm) };
    stk::Stackable_ptr first  { Asm::pop(rvm) };
    
    stk::Stackable_ptr nouveau { new stk::Number { 
        func(dynamic_cast<stk::Number*>(first.get())->get(), 
             dynamic_cast<stk::Number*>(second.get())->get()) 
    }};
    Asm::push(rvm, std::move(nouveau));
}

void Asm::ADD(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a + b; });
}

void Asm::SUB(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a - b; });
}

void Asm::MUL(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a * b; });
}

void Asm::DIV(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a / b; });
}

void Asm::MOD(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a % b; });
}
