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

#ifndef HPP_STK_ADDRESS_DEFINED
#define HPP_STK_ADDRESS_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Internal libraries
#include "Stackable.hpp"

namespace stk
{
    /**
     * @class Address
     * 
     * @brief **Stores a positive integer with a program address**
     * 
     * Adresses can be used by any assembly opcode wich can manage
     * memory (E.g: JMP, JIF, JIT). They are always strictly positive.
     * 
     * An adress is a stackable and can be put in the main stack
     * of a virtual machine.
     * 
     * @see Stackable
     * @see RVM
     *
     * @author Renato Cordeiro Ferreira
     */
    class Address: public Stackable
    {
        private:
            unsigned int address;
        
        public:
            /** 
             * <b>Default constructor.</b>
             * 
             * @param a Address to be stored in this object.
             */
            Address(unsigned int a = 0)
                : Stackable(Stackable::Type::Address), 
                  address{a} {}
            
            /// @return Address defined in the construction
            unsigned int get() const { return this->address; }
            
            std::string to_string() const
            { return std::to_string(this->address); }
            
            Address *clone()  const { return new Address{*this}; }
            Address *create() const { return new Address{};      }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Address& n);
    };
            
    std::ostream& operator<<(std::ostream& os, const Address& n);
}

#endif
