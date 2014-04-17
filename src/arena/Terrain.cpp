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

// Libraries
#include "Terrain.hpp"
using namespace arena;

Terrain::Type Terrain::app2type(Appearence app) const
{
    switch (app)
    {
        case App::DEEP   : return Type::BLOCKED; break;
        
        case App::DIRT   : return Type::NORMAL;  break;
        case App::GRASS  : return Type::NORMAL;  break;
        case App::TUNDRA : return Type::NORMAL;  break;
        
        case App::ROCKY  : return Type::ROUGH;   break;
        case App::ICE    : return Type::ROUGH;   break;
        case App::JUNGLE : return Type::ROUGH;   break;
        case App::WATER  : return Type::ROUGH;   break;
        case App::SAND   : return Type::ROUGH;   break;
        
        default:
            // TODO: Throw exception
            return Type::NORMAL;
    }
}

std::string arena::to_string(const Terrain::Type type)
{
    switch(type)
    {
        case Terrain::Type::NORMAL:  return "NORMAL";
        case Terrain::Type::ROUGH:   return "ROUGH";
        case Terrain::Type::BLOCKED: return "BLOCKED";
    }
    return "Terrain2string: Should not happen";
}

std::string arena::to_string(const Terrain::Appearence app)
{
    switch(app)
    {
        case Terrain::Appearence::DEEP:   return "DEEP"; 
        case Terrain::Appearence::DIRT:   return "DIRT"; 
        case Terrain::Appearence::GRASS:  return "GRASS"; 
        case Terrain::Appearence::ROCKY:  return "ROCKY"; 
        case Terrain::Appearence::ICE:    return "ICE"; 
        case Terrain::Appearence::WATER:  return "WATER"; 
        case Terrain::Appearence::SAND:   return "SAND"; 
        case Terrain::Appearence::JUNGLE: return "JUNGLE"; 
        case Terrain::Appearence::TUNDRA: return "TUNDRA";
    }
    return "Appearence2string: Should not happen";
}

std::ostream& 
arena::operator<<(std::ostream& os, const Terrain::Type& t)
{
    os << to_string(t);
    return os;
}

std::ostream& 
arena::operator<<(std::ostream& os, const Terrain::Appearence& a)
{
    os << to_string(a);
    return os;
}

std::ostream& 
arena::operator<<(std::ostream& os, const Terrain& t)
{
    os << "[ " << t.get_appearence() << ":";
    os << to_string(t.get_type())[0] << " ]";
    return os;
}
