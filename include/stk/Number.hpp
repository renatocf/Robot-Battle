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

#ifndef HPP_STK_NUMBER_DEFINED
#define HPP_STK_NUMBER_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Internal libraries
#include "Stackable.hpp"

namespace stk
{
    class Number: public Stackable
    {
        private:
            enum class Type { Integer, Float };
            
            Type type;
            const union {
                int l;
                double d;
            };
        
        public:
            Number(int l = 0)
                : Stackable(Stackable::Type::Number), 
                  type{Type::Integer}, l{l} {}
            Number(double d)
                : Stackable(Stackable::Type::Number), 
                  type{Type::Float}, d{d}   {}
            
            int get() const;
            
            std::string to_string() const
            {
                return this->type == Type::Integer
                    ? std::to_string(this->l)
                    : std::to_string(this->d);
            }
            
            Number *clone() const
            {
                return new Number{*this};
            }
            
            Number *create() const
            {
                return new Number{};
            }
            
            virtual const Number& typeref() const
            {
                return *this;
            }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Number& n);
    };
            
    std::ostream& operator<<(std::ostream& os, const Number& n);
}

#endif
