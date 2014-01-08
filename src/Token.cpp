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

// Default libraries
#include <iostream>

// Libraries
#include "Token.hpp"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 TOKEN                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream& operator<<(std::ostream& os, const Token& t)
{
    switch(t.type)
    {
        case Type::NUMBER:
            os << "[NUMBER:" << t.n << "]";
            break;
        case Type::OPERATOR: 
            os << "[OPERATOR:" << t.o << "]";
            break;
        case Type::UNDEFINED: 
            os << "[UNDEFINED:]";
            break;
        default: 
            os << "[TOKEN:Should not happen]";
    }
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                SENTENCE                                 
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream &operator<<(std::ostream &os, const Sentence& sent)
{
    bool first = true;
    for(Token token : sent)
    {
        (first) ? first = false : os << " ";
        os << token;
    }
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  TEXT                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream &operator<<(std::ostream &os, const Text& text)
{
    bool first = true;
    for(Sentence sent : text)
    {
        (first) ? first = false : os << std::endl;
        os << sent;
    }
    return os;
}
