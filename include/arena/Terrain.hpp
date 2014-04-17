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

#ifndef HPP_ARENA_TERRAIN_DEFINED
#define HPP_ARENA_TERRAIN_DEFINED

// Default libraries
#include <vector>

// Libraries
#include "stk.hpp"

namespace arena 
{
    class Terrain : public stk::Vision
    {
        public:
            enum class Type {
                NORMAL, ROUGH, BLOCKED
            };
            
            enum class Appearence {
                DEEP, DIRT, GRASS, ROCKY, ICE, 
                WATER, SAND, JUNGLE, TUNDRA
            };
            
        private:
            using App = Appearence;
            
            mutable Appearence app              {};
            mutable Type type                   {};
            
            mutable std::vector<bool> fog        {};
            mutable std::vector<bool> visibility {};
            
            Type app2type(Appearence app);
            
        public:
            Terrain(int nPlayers, Appearence app)
                : stk::Vision{"Terrain"}, 
                  app{app}, type{app2type(app)}, 
                  fog(nPlayers,false), visibility(nPlayers,false) {}
            
            // Getters
            Type       get_type()       { return this->type; }
            Appearence get_appearence() { return this->app;  }
    };
}

#endif
