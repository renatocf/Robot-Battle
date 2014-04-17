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

#ifndef HPP_STK_VISION_DEFINED
#define HPP_STK_VISION_DEFINED

// Default libraries
#include <string>

// Internal libraries
#include "Stackable.hpp"

namespace stk 
{
    class Vision : public Stackable
    {
        private:
            std::string vision;
        
        public:
            /** 
             * <b>Default constructor.</b>
             * 
             * @param vision Vision to be stored in this object.
             */
            Vision(std::string vision = "")
                : Stackable{Type::Vision}, vision{vision} {}
            
            /// @return Address defined in the construction
            std::string get() const { return this->vision; }
            
            std::string to_string() const
            { return this->vision; }
            
            Vision *clone()  const { return new Vision{*this}; }
            Vision *create() const { return new Vision{};      }
            
            friend std::ostream&
            operator<<(std::ostream& os, const Vision& n);
    };
            
    std::ostream& operator<<(std::ostream& os, const Vision& n);
}

#endif
