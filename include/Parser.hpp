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

#ifndef HPP_PARSER_DEFINED
#define HPP_PARSER_DEFINED

// Default libraries
#include <string>

// Libraries
#include "Token.hpp"

class Parser
{
    private:
        Text text;
        
    public:
        // Text() 
            // : is{std::cin} 
        // {}
        // Text(std::istream is)
            // : is{is} {}
        
        // Getters
        const Text& getText() const { return text; }
        
        void  reInit (std::istream& is);
        Text& parse  (std::string prompt = "> ");
        Text& parse  (std::istream& is);
        
    private:
        void infix_to_posfix();
};

#endif
