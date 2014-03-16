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
 * @file   Arith.cpp
 * @brief  Provide assembly arithmetic operations for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Asm.hpp"
#include "Debug.hpp"
#include "Number.hpp"
using namespace vm;

/**
 * Assembly auxiliar function operate. <br>
 * Auxiliar to execute a binary arithmetic operation 
 * over the two top most stackable in the main stack 
 * of a Virtual Machine.
 * @param rvm  Robot Virtual Machine
 * @param func Lambda function with a binary arithmetic operation
 */
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

/**
 * Assembly function ADD. <br>
 * Sum the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::ADD(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a + b; });
}

/**
 * Assembly function SUB. <br>
 * Subtract the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::SUB(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a - b; });
}

/**
 * Assembly function MUL. <br>
 * Multiply the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::MUL(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a * b; });
}

/**
 * Assembly function DIV. <br>
 * Divide the two top most stackable (second / first) of a RVM 
 * and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::DIV(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a / b; });
}

/**
 * Assembly function MOD. <br>
 * Get the remainder of the division of the two top most 
 * stackable (second % first) of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::MOD(const RVM& rvm)
{
    operate(rvm, [] (long long a, long long b) { return a % b; });
}
