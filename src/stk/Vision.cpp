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
#include "Vision.hpp"
using namespace stk;

/**
 * Overload the operator << to print Vision. <br>
 * @param  os   Standard output streams to print
 * @param  addr Stackable vision to be printed
 * @return Standard output stream received as argument
 */
std::ostream& stk::operator<<(std::ostream& os, const Vision& vision)
{
    os << vision;
    return os;
}
