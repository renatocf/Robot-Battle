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
            
            Type app2type(Appearence app) const;
            
        public:
            Terrain(int nPlayers, Appearence app = Appearence::GRASS)
                : stk::Vision{"Terrain"}, 
                  app{app}, type{app2type(app)}, 
                  fog(nPlayers,false), visibility(nPlayers,false) {}
            
            // Getters
            Type       get_type()       const { return this->type; }
            Appearence get_appearence() const { return this->app;  }
        
            friend std::ostream& 
            operator<<(std::ostream& os, const Terrain& t);
    };
    
    std::string to_string(const Terrain::Type type);
    std::string to_string(const Terrain::Appearence app);
    
    std::ostream& 
    operator<<(std::ostream& os, const Terrain::Type& t);
    
    std::ostream& 
    operator<<(std::ostream& os, const Terrain::Appearence& a);
    
    std::ostream& 
    operator<<(std::ostream& os, const Terrain& t);
}

#endif
