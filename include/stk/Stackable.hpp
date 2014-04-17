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

#ifndef HPP_STK_STACKABLE_DEFINED
#define HPP_STK_STACKABLE_DEFINED

// Default libraries
#include <string>
#include <memory>
#include <iostream>

namespace stk
{
    /**
     * @class Stackable
     * 
     * @brief **Type of element that can be stored in a RVM**
     *
     * This class is the base of a class hierarchy with the 
     * default types accepted by the main stack (DATA) of a RVM.
     * 
     * @see    RVM
     * @author Renato Cordeiro Ferreira
     */
    class Stackable 
    {
        public:
            /**
             * @enum Type
             * Subtypes of the stackable.
             */
            enum class Type { Int, Float, Text, Address, Vision };
            
            /// Underlying type of the stackable.
            const Type type;
            
            /// <p>Default destructor.</p>
            virtual ~Stackable() {}
            
            /// @return String representing the stackable
            virtual std::string to_string() const = 0;
            
            /// @return Pointer to a clone of the stackable,
            ///         built in the heap
            virtual Stackable        *clone  () const = 0;
            
            /// @return New stackable subtype with default value,
            ///         built in the heap
            virtual Stackable        *create () const = 0;
        
        protected:
            /**
             * <b>Default constructor.</b>
             * No instances of this class allowed.
             */
            Stackable(Type t)
                : type{t} {}
            
        public:
            friend std::ostream& 
            operator<<(std::ostream& os, const Stackable& stk);
    };
    
    /**
     * Outputs a stackable.
     * @param  os  Output stream
     * @param  stk Stackable to have its content outputed
     * @return Reference to output stream
     */
    std::ostream& operator<<(std::ostream& os, const Stackable& stk);
    
    /**
     * @def Stackable_ptr
     * Shortcut to pointer to a stackable. Works as a shared pointer
     * and properly does the garbage collector when there is no more
     * pointers to the stackable.
     */
    using Stackable_ptr = std::shared_ptr<stk::Stackable>;
    
    /**
     * Outputs the pointed object of a stackable pointer.
     * @param  os  Output stream
     * @param  stk Stackable_ptr to have its pointed object outputed
     * @return Reference to output stream
     */
    std::ostream& operator<<(std::ostream& os, const Stackable_ptr& stk);
}

#endif
