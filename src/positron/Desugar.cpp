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
        case ExprS::Sugar::intS: 
            return new intC{
                dynamic_cast<const intS *>(node)->get()};
        
        case ExprS::Sugar::floatS: 
            return new floatC{
                dynamic_cast<const floatS *>(node)->get()};
        
        case ExprS::Sugar::idS: 
            return new idC{
                dynamic_cast<const idS *>(node)->get()};
        
        case ExprS::Sugar::lamS:
            return new lamC{ 
                static_cast<const idC *>(desugar(node->l)), 
                desugar(node->r)};
        
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
        
        case ExprS::Sugar::appS:
            return new appC{ 
                desugar(node->l), desugar(node->r)};
        
        case ExprS::Sugar::uminusS:
            return new multC{
                new intC{-1}, desugar(node->l)};
            
        default:
            std::cerr << "Should not happen" << std::endl;
            return new intC{1};
    }
    return new intC{1};
}
