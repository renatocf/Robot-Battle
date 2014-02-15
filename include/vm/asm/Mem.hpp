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

#ifndef HPP_VM_MEM_DEFINED
#define HPP_VM_MEM_DEFINED

namespace vm
{
    inline void 
    STO(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
    {
        int pos = dynamic_cast<stk::Address>(stk).get();
        rvm.RAM[pos] = stk::Stackable_ptr { stk->clone() };
    }
    
    inline stk::Stackable_ptr
    RCL(const vm::RVM& rvm, const stk::Stackable_ptr& stk)
    {
        int pos = dynamic_cast<stk::Address>(stk).get();
        stk::Stackable_ptr ret { std::move(rvm.RAM[pos]) };
        return ret;
    }
}

#endif
