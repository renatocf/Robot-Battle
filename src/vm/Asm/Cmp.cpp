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

#include <iostream>
#include <typeinfo>

// Libraries
#include "Asm.hpp"
#include "Bool.hpp"
#include "Text.hpp"
#include "Debug.hpp"
#include "Number.hpp"
#include "Address.hpp"
#include "Stackable.hpp"
using namespace vm;

template<typename T, typename F> 
void Asm::compare(
    const RVM& rvm, 
    const stk::Stackable_ptr& arg1, 
    const stk::Stackable_ptr& arg2, 
    F cmp)
{
    T* arg1_ptr = dynamic_cast<T*>(arg1.get());
    T* arg2_ptr = dynamic_cast<T*>(arg2.get());
    
    Asm::push(rvm, stk::Stackable_ptr { 
        new stk::Bool { cmp(arg1_ptr->get(), arg2_ptr->get()) ? true : false }
    });
}

template<typename F> 
void Asm::select(const RVM& rvm, F cmp)
{
    stk::Stackable_ptr arg2 { Asm::pop(rvm) };
    stk::Stackable_ptr arg1 { Asm::pop(rvm) };
    
    if(arg1->type == arg2->type)
    {
        switch(arg1->type)
        {
            case stk::Stackable::Type::Number:
                Asm::compare<stk::Number>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Text:    
                Asm::compare<stk::Text>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Address: 
                Asm::compare<stk::Address>(rvm, arg1, arg2, cmp);
                break;
            case stk::Stackable::Type::Bool: 
                Asm::compare<stk::Bool>(rvm, arg1, arg2, cmp);
                break;
        }
    }
    Debug::printStack(rvm);
}

struct eq
{
    template<typename T>
    bool operator() (T x, T y) const { return x == y; }
};

void Asm::EQ(const vm::RVM& rvm)
{
    Asm::select(rvm, eq {});
}

struct ne
{
    template<typename T>
    bool operator() (T x, T y) const { return x != y; }
};

void Asm::NE(const vm::RVM& rvm)
{
    Asm::select(rvm, ne {});
}

struct gt
{
    template<typename T>
    bool operator() (T x, T y) const { return x > y; }
};

void Asm::GT(const vm::RVM& rvm)
{
    Asm::select(rvm, gt {});
}

struct ge
{
    template<typename T>
    bool operator() (T x, T y) const { return x >= y; }
};

void Asm::GE(const vm::RVM& rvm)
{
    Asm::select(rvm, ne {});
}

struct lt
{
    template<typename T>
    bool operator() (T x, T y) const { return x < y; }
};

void Asm::LT(const vm::RVM& rvm)
{
    Asm::select(rvm, lt {});
}

struct le
{
    template<typename T>
    bool operator() (T x, T y) const { return x <= y; }
};

void Asm::LE(const vm::RVM& rvm)
{
    Asm::select(rvm, le {});
}
