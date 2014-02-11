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
    class Stackable 
    {
        protected:
            enum class Type { Number };
            
        public:
            virtual std::string to_string() const = 0;
            virtual ~Stackable() {}
            
            virtual Stackable *clone() const = 0;
            virtual Stackable *create() const = 0;
        
        protected:
            Type type;
            Stackable(Type t)
                : type{t} {}
            
        public:
            friend std::ostream& 
            operator<<(std::ostream& os, const Stackable& stk);
    };
    
    std::ostream& operator<<(std::ostream& os, const Stackable& stk);
    
    using Stackable_ptr = std::unique_ptr<stk::Stackable>;
}

#endif
