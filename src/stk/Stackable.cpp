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
 * @file   Stackable.cpp
 * @brief  Base of a class hierarchy of types stackable by RVM.
 * @author Renato Cordeiro Ferreira
 */

// Libraries
#include "Stackable.hpp"

/**
 * Overload the operator << to print any stackable. <br>
 * @param  os   Standard output streams to print
 * @param  addr Stackable to be printed
 * @return Standard output streams received as argument
 */
std::ostream& 
stk::operator<<(std::ostream& os, const stk::Stackable& stk)
{
    os << stk.to_string();
    return os;
}

/**
 * Overload the operator << to print any stackable pointer. <br>
 * @param  os   Standard output streams to print
 * @param  addr Reference to pointer of the stackable to be printed
 * @return Standard output stream received as argument
 */
std::ostream& 
stk::operator<<(std::ostream& os, const stk::Stackable_ptr& stk)
{
    if(stk) os << stk->to_string();
    return os;
}
