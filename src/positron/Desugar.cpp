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
#include "Desugar.hpp"
using namespace positron;

ExprC *Desugar::desugar(const ExprS *node) const
{
    if(node) switch(node->type)
    {
        case ExprS::Sugar::numS: 
            return new numC{
                dynamic_cast<const numS *>(node)->get()};
        
        case ExprS::Sugar::plusS:
            return new plusC{ 
                desugar(node->l), desugar(node->r)};
        
        case ExprS::Sugar::bminusS:
            return new bminusC{
                desugar(node->l), desugar(node->r)};
        
        case ExprS::Sugar::multS: 
            return new multC{ 
                desugar(node->l), desugar(node->r)};
        
        case ExprS::Sugar::divS:
            return new divC{ 
                desugar(node->l), desugar(node->r)};
        
        case ExprS::Sugar::ifS:
            return new ifC{ desugar(node->l), 
                desugar(node->r), desugar(node->x)};
        
        case ExprS::Sugar::uminusS:
            return new multC{
                new numC{-1}, desugar(node->l)};
            
        default:
            std::cerr << "Should not happen" << std::endl;
            return new numC{1};
    }
    return new numC{1};
}
