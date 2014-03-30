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

#ifndef HPP_PARSER_DESUGAR_DEFINED
#define HPP_PARSER_DESUGAR_DEFINED

// Libraries
#include "Syntax_C.hpp"
#include "Syntax_S.hpp"

namespace parser 
{
    class Desugar
    {
        public:
            ExprC *desugar(const ExprS& root) const
            {
                return desugar(&root);
            }
            
            ExprC *desugar(const ExprS *node) const;
    };
}

#endif
