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
 * @file   Asm.hpp
 * @brief  Class with definition of the assembly functions of a RVM.
 * @author Renato Cordeiro Ferreira
 */

#ifndef HPP_VM_ASM_DEFINED
#define HPP_VM_ASM_DEFINED

// Libraries
#include "stk.hpp"
#include "RVM.hpp"

namespace vm
{
    class Asm
    {
        private:
            using Stk_ptr = stk::Stackable_ptr;
            
        public:
            // Exceptions
            struct invalid_type {};
             
            // Stack functions
            static void PUSH (const vm::RVM& rvm, const Stk_ptr& stk);
            static void POP  (const vm::RVM& rvm);
            static void SWAP (const vm::RVM& rvm);
            static void DUP  (const vm::RVM& rvm);
            
            // Arithmetic functions
            static void ADD  (const vm::RVM& rvm);
            static void SUB  (const vm::RVM& rvm);
            static void MUL  (const vm::RVM& rvm);
            static void DIV  (const vm::RVM& rvm);
            static void MOD  (const vm::RVM& rvm);
            
            // Memory functions
            static void STO  (const vm::RVM& rvm, const Stk_ptr& stk);
            static void RCL  (const vm::RVM& rvm, const Stk_ptr& stk);
            
            // Comparison functions
            static void EQ   (const vm::RVM& rvm);
            static void NE   (const vm::RVM& rvm);
            static void GT   (const vm::RVM& rvm);
            static void GE   (const vm::RVM& rvm);
            static void LT   (const vm::RVM& rvm);
            static void LE   (const vm::RVM& rvm);
            
            // IO functions
            static void PRN  (const vm::RVM& rvm);
            
            // Jump functions
            static void JMP  (const vm::RVM& rvm, const Stk_ptr& stk);
            static void JIT  (const vm::RVM& rvm, const Stk_ptr& stk);
            static void JIF  (const vm::RVM& rvm, const Stk_ptr& stk);
            
            // Syscall functions
            static void NOP  (const vm::RVM& rvm);
            static void END  (const vm::RVM& rvm);
            
        private:
            // Stack auxiliar    
            static void 
            push(const vm::RVM& rvm, const Stk_ptr& stk);
            
            static Stk_ptr 
            pop(const vm::RVM& rvm);
            
            // Arithmetic auxiliar
            template<typename Func>
            static void operate(const vm::RVM& rvm, Func func);
            
            // Comparison auxiliar
            template<typename T, typename Func>
            static void compare(
                const RVM& rvm, 
                const Stk_ptr& arg1, 
                const Stk_ptr& arg2, 
                Func cmp
            );
            
            template<typename Func> 
            static void select(const RVM& rvm, Func cmp);
            
            // Jump auxiliar
            template<typename Func>
            static void JCMP(
                const RVM& rvm, 
                const Stk_ptr& stk, 
                Func cmp,
                bool pop = true
            );
    };
}

#endif
