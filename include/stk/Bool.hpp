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

#ifndef HPP_STK_BOOL_DEFINED
#define HPP_STK_BOOL_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Internal libraries
#include "Stackable.hpp"

namespace stk
{
    class Bool: public Stackable
    {
        private:
            bool boolean;
        
        public:
            Bool(int a = 0)
                : Stackable(Stackable::Type::Bool), 
                  boolean{ (a != 0) ? true : false } {}
            Bool(bool b)
                : Stackable(Stackable::Type::Bool), 
                  boolean{b} {}
            
            bool get() const
            {
                return this->boolean;
            }
            
            std::string to_string() const
            {
                return (this->boolean) ? "true" : "false";
            }
            
            Bool *clone() const
            {
                return new Bool{*this};
            }
            
            Bool *create() const
            {
                return new Bool{};
            }
            
            virtual const Bool& typeref() const
            {
                return *this;
            }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Bool& b);
    };
            
    std::ostream& operator<<(std::ostream& os, const Bool& b);
}

#endif
