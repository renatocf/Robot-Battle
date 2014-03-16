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
 * @file   Syscall.cpp
 * @brief  Provide assembly system call operations for a RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Asm.hpp"
#include "Debug.hpp"
using namespace vm;

/**
 * Assembly funcion NOP. <br>
 * Do nothing for one step.
 * (Equivalent to a syscall)
 * @param rvm Robot Virtual Machine
 */
void Asm::NOP(const RVM& rvm) 
{ 
    rvm.syscall = true;
    /* Syst.SKIP(rvm); */ 
}

/**
 * Assembly funcion END. <br>
 * Sets the counter to indicate
 * the END of the program.
 * the execution for 1 step.
 * @param rvm Robot Virtual Machine
 */
void Asm::END(const RVM& rvm) 
{ 
    rvm.syscall = true;
    rvm.PC = -1; /* Syst.SKIP(rvm); */ 
}
// Sets the counter to -1, to be able to
// increment in each iteration of a for loop.
