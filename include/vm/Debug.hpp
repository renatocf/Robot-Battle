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

#ifndef HPP_VM_DEBUG_DEFINED
#define HPP_VM_DEBUG_DEFINED

// Internal libraries
#include "RVM.hpp"
#include "Command.hpp"

namespace vm 
{
    class Debug 
    {
        private:
        
        public:
            static bool OFF; /* TODO: Make private */
            static void printRAM     (const vm::RVM& rvm);
            static void printStack   (const vm::RVM& rvm);
            static void printCommand (const vm::RVM& rvm, int pos);
        
        private:
            Debug() {} // No instances of this 
                       // class allowed
    };
}

#endif
