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

#ifndef HPP_ARENA_MAP_DEFINED
#define HPP_ARENA_MAP_DEFINED

// Default libraries
#include <vector>

// Libraries
#include "Terrain.hpp"

namespace arena 
{
    class Map
    {
        template<typename T>
        using matrix = std::vector<std::vector<T>>;
        
        private:
            matrix<Terrain> map {};
        
        public:
            Map(matrix<Terrain> map = {})
                : map{map} {}
        
            friend std::ostream& 
            operator<<(std::ostream& os, const Map& n);
    };
    
    std::ostream& operator<<(std::ostream& os, const Map& n);
}

#endif
