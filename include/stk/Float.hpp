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

#ifndef HPP_STK_FLOAT_DEFINED
#define HPP_STK_FLOAT_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Floaternal libraries
#include "Stackable.hpp"

namespace stk
{
    class Float: public Stackable
    {
        private:
            float f;
        
        public:
            /** 
             * <b>Default constructor.</b>
             * 
             * @param f Floating point to be stored in this object.
             */
            Float(float f = 0.0)
                : Stackable(Stackable::Type::Float), f{f} {}
            
            /// @return Address defined in the construction
            float get() const { return this->f; }
            
            std::string to_string() const
            { return std::to_string(this->f); }
            
            Float *clone()  const { return new Float{*this}; }
            Float *create() const { return new Float{};      }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Float& n);
    };
            
    std::ostream& operator<<(std::ostream& os, const Float& n);
}

#endif
