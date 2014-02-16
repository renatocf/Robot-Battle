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

#ifndef HPP_STK_TEXT_DEFINED
#define HPP_STK_TEXT_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Internal libraries
#include "Stackable.hpp"

namespace stk
{
    class Text: public Stackable
    {
        private:
            std::string text;
        
        public:
            Text(std::string text = "")
                : Stackable{Type::Text}, text{text} {}
            
            std::string get() const
            {
                return this->text;
            }
            
            std::string to_string() const
            {
                return this->text;
            }
            
            Text *clone() const
            {
                return new Text{*this};
            }
            
            Text *create() const
            {
                return new Text{};
            }
            
            const Text& typeref () const 
            {
                return *this;
            }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Text& n);
    };
            
    std::ostream& operator<<(std::ostream& os, const Text& n);
}

#endif
