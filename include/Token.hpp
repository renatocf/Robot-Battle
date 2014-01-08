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

#ifndef HPP_TOKEN_DEFINED
#define HPP_TOKEN_DEFINED

// Default libraries
#include <vector>
#include <iostream>

// Enum Type
enum class Type { UNDEFINED, NUMBER, OPERATOR };

// Aliases
using number_t   = int;
using operator_t = char;

struct Token
{
    const Type type;
    const union {
        number_t   n;
        operator_t o;
    };
    
    // Constructors
    Token() 
        : type{Type::UNDEFINED}, n{0} {}
    Token(Type t, number_t n) 
        : type{t}, n{n} {}
    Token(Type t, operator_t o) 
        : type{t}, o{o} {}
    
    // Destructor
    ~Token() {}
    
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

using Sentence = std::vector<Token>;
std::ostream &operator<<(std::ostream &os, const Sentence& sent);

using Text = std::vector<Sentence>;
std::ostream &operator<<(std::ostream &os, const Text& text);

#endif
