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

#ifndef HPP_STK_INT_DEFINED
#define HPP_STK_INT_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Internal libraries
#include "Stackable.hpp"

namespace stk
{
    class Int: public Stackable
    {
        private:
            int i;
        
        public:
            /** 
             * <b>Default constructor.</b>
             * 
             * @param i Integer to be stored in this object.
             */
            Int(int i = 0)
                : Stackable(Stackable::Type::Int), i{i} {}
            
            /// @return Address defined in the construction
            int get() const { return this->i; }
            
            std::string to_string() const
            { return std::to_string(this->i); }
            
            Int *clone()  const { return new Int{*this}; }
            Int *create() const { return new Int{};      }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Int& n);
    };
    
    std::ostream& operator<<(std::ostream& os, const Int& n);
}

#endif
