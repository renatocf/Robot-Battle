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
#include "Int.hpp"
#include "Debug.hpp"
#include "Float.hpp"
using namespace vm;

/**
 * Assembly auxiliar function operate. <br>
 * Auxiliar to execute a binary arithmetic operation 
 * over the two top most stackable in the main stack 
 * of a Virtual Machine.
 * @param rvm  Robot Virtual Machine
 * @param func Lambda function with a binary arithmetic operation
 */
template<class Func>
void Asm::operate(const RVM& rvm, Func func)
{
    using namespace stk;
    Stackable_ptr second { Asm::pop(rvm) };
    Stackable_ptr first  { Asm::pop(rvm) };
    
    if(first->type == Stackable::Type::Int 
    && second->type == Stackable::Type::Int)
    {
        Asm::push(rvm, Stackable_ptr { new Int { 
            func(dynamic_cast<Int*>(first.get())->get(), 
                 dynamic_cast<Int*>(second.get())->get()) 
        }});
    }
    else if(first->type == Stackable::Type::Float
         && second->type == Stackable::Type::Int)
    {
        Asm::push(rvm, Stackable_ptr { new Float { 
            func(dynamic_cast<Float*>(first.get())->get(), 
                 dynamic_cast<Int*>(second.get())->get())
        }});
    }
    else if(first->type == Stackable::Type::Int
         && second->type == Stackable::Type::Float)
    {
        Asm::push(rvm, Stackable_ptr { new Float { 
            func(dynamic_cast<Int*>(first.get())->get(),
                 dynamic_cast<Float*>(second.get())->get())
        }});
    }
    else
    {
        Asm::push(rvm, Stackable_ptr { new Float { 
            func(dynamic_cast<Float*>(first.get())->get(), 
                 dynamic_cast<Float*>(second.get())->get()) 
        }});
    }
}

/**
 * Auxiliar functor for the + operation. <br>
 * Provides a template of the operation above for Int and Float types
 */
struct p_add
{
    /// Overload the operator () to provide a functor.
    template<typename X, typename Y>
    float operator() (X   x, Y   y) const { return x + y; }
    int   operator() (int x, int y) const { return x + y; }
};

/**
 * Assembly function ADD. <br>
 * Sum the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::ADD(const RVM& rvm)
{
    operate(rvm, p_add{});
}

/**
 * Auxiliar functor for the - operation. <br>
 * Provides a template of the operation above for Int and Float types
 */
struct p_sub
{
    /// Overload the operator () to provide a functor.
    template<typename X, typename Y>
    float operator() (X   x, Y   y) const { return x - y; }
    int   operator() (int x, int y) const { return x - y; }
};

/**
 * Assembly function SUB. <br>
 * Subtract the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::SUB(const RVM& rvm)
{
    operate(rvm, p_sub{});
}

/**
 * Auxiliar functor for the * operation. <br>
 * Provides a template of the operation above for Int and Float types
 */
struct p_mul
{
    /// Overload the operator () to provide a functor.
    template<typename X, typename Y>
    float operator() (X   x, Y   y) const { return x * y; }
    int   operator() (int x, int y) const { return x * y; }
};

/**
 * Assembly function MUL. <br>
 * Multiply the two top most stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::MUL(const RVM& rvm)
{
    operate(rvm, p_mul{});
}

/**
 * Auxiliar functor for the / operation. <br>
 * Provides a template of the operation above for Int and Float types
 */
struct p_div
{
    /// Overload the operator () to provide a functor.
    template<typename X, typename Y>
    float operator() (X   x, Y   y) const { return x / y; }
    int   operator() (int x, int y) const { return x / y; }
};

/**
 * Assembly function DIV. <br>
 * Divide the two top most stackable (second / first) of a RVM 
 * and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::DIV(const RVM& rvm)
{
    operate(rvm, p_div{});
}

/**
 * Auxiliar functor for the % operation. <br>
 * Provides a template to the operation above for Int.
 * Throws an 'invalid_type' exception otherwise.
 */
struct p_mod
{
    /// Overload the operator () to provide a functor.
    template<typename X, typename Y>
    float operator() (X   x, Y   y) const { throw Asm::invalid_type{}; }
    int   operator() (int x, int y) const { return x % y; }
};

/**
 * Assembly function MOD. <br>
 * Get the remainder of the division of the two top most 
 * stackable (second % first) of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::MOD(const RVM& rvm)
{
    operate(rvm, p_mod{});
}
