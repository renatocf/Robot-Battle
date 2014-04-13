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
 * @file   Cmp.cpp
 * @brief  Provide assembly comparison operations for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Asm.hpp"
#include "Int.hpp"
#include "Text.hpp"
#include "Float.hpp"
#include "Debug.hpp"
#include "Address.hpp"
#include "Stackable.hpp"
using namespace vm;

/**
 * Assembly auxiliar function compare. <br>
 * Auxiliar to execute a binary comparison operation 
 * over its arguments and push the answer in a RVM.
 * @param rvm  Robot Virtual Machine
 * @param arg1 First argument for the binary comparison function
 * @param arg2 Second argument for the binary comparison function
 * @param cmp  Comparison function
 */
template<typename T, typename Func>
void Asm::compare(
    const RVM& rvm, 
    const stk::Stackable_ptr& arg1, 
    const stk::Stackable_ptr& arg2, 
    Func cmp)
{
    T* arg1_ptr = dynamic_cast<T*>(arg1.get());
    T* arg2_ptr = dynamic_cast<T*>(arg2.get());
    
    Asm::push(rvm, stk::Stackable_ptr { 
        new stk::Int { cmp(arg1_ptr->get(), arg2_ptr->get()) ? 1 : 0 }
    });
}

/**
 * Assembly auxiliar function select. <br>
 * Auxiliar to execute a binary comparison operation 
 * over the two top most stackable in the main stack 
 * of a Virtual Machine (accordingly to its type).
 * @param rvm Robot Virtual Machine
 * @param cmp Comparison function to be executed over the arguments
 */
template<typename Func> 
void Asm::select(const RVM& rvm, Func cmp)
{
    stk::Stackable_ptr arg2 { Asm::pop(rvm) };
    stk::Stackable_ptr arg1 { Asm::pop(rvm) };
    
    if(arg1->type == arg2->type)
    {
        switch(arg1->type)
        {
            case stk::Stackable::Type::Int:
                Asm::compare<stk::Int>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Float:
                Asm::compare<stk::Float>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Text:    
                Asm::compare<stk::Text>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Address: 
                Asm::compare<stk::Address>(rvm, arg1, arg2, cmp);
                break;
        }
    }
    Debug::printStack(rvm);
}

/**
 * Auxiliar functor for the 'equal' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct eq
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x == y; }
};

/**
 * Assembly function EQ. <br>
 * Compare for equality the two top most stackable of a RVM 
 * and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::EQ(const vm::RVM& rvm)
{
    Asm::select(rvm, eq {});
}

/**
 * Auxiliar functor for the 'not equal' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct ne
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x != y; }
};

/**
 * Assembly function NE. <br>
 * Compare for inequality the two top most stackable of a RVM 
 * and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::NE(const vm::RVM& rvm)
{
    Asm::select(rvm, ne {});
}

/**
 * Auxiliar functor for the 'greater than' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct gt
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x > y; }
};

/**
 * Assembly function GT. <br>
 * Execute the greater than operation over the two top most 
 * stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::GT(const vm::RVM& rvm)
{
    Asm::select(rvm, gt {});
}

/**
 * Auxiliar functor for the 'greater or equal' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct ge
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x >= y; }
};

/**
 * Assembly function GE. <br>
 * Execute the greater or equal operation over the two top most 
 * stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::GE(const vm::RVM& rvm)
{
    Asm::select(rvm, ne {});
}

/**
 * Auxiliar functor for the 'less than' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct lt
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x < y; }
};

/**
 * Assembly function LT. <br>
 * Execute the less than operation over the two top most 
 * stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::LT(const vm::RVM& rvm)
{
    Asm::select(rvm, lt {});
}

/**
 * Auxiliar functor for the 'less or equal' operation. <br>
 * Provides a template for the operation above in any type.
 */
struct le
{
    /// Overload the operator () to provide a functor.
    template<typename T>
    bool operator() (T x, T y) const { return x <= y; }
};

/**
 * Assembly function LE. <br>
 * Execute the less or equal operation over the two top most 
 * stackable of a RVM and push the result.
 * @param rvm Robot Virtual Machine
 */
void Asm::LE(const vm::RVM& rvm)
{
    Asm::select(rvm, le {});
}
