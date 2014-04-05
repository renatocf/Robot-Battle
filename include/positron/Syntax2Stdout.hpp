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

#ifndef HPP_POSITRON_SYNTAX2STDOUT_DEFINED
#define HPP_POSITRON_SYNTAX2STDOUT_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Libraries
#include "Number.hpp"
#include "Syntax_C.hpp"

namespace positron
{
    class Syntax2Stdout : public Visitor
    {
        private:
            mutable std::vector<std::string> separator {};
            
        public:
            void visit(const numC *exprC) const 
            {
                if(exprC == nullptr) return;
                stk::Stackable_ptr num { new stk::Number {
                    dynamic_cast<const numC *>(exprC)->get()
                }};
                std::cout << num << std::endl;
            }
            
            void visit(const plusC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "plusC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "|  ");
            }
            
            void visit(const bminusC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "bminusC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "|  ");
            }
            
            void visit(const multC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "multC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "|  ");
            }
            
            void visit(const divC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "divC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "|  ");
            }
            
            void visit(const ifC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "ifC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "|- ", "|  ");
                visit_x(exprC, "'- ", "   ");
            }

        private:
            void visit_l(
                const ExprC *exprC, 
                std::string itm, 
                std::string sep) const
            {
                if(exprC == nullptr) return;
                for(std::string s : separator) std::cout << s;
                std::cout << itm; separator.push_back(sep);
                exprC->accept_l(*this);
                separator.pop_back();
            }
            
            void visit_r(
                const ExprC *exprC, 
                std::string itm, 
                std::string sep) const
            {
                if(exprC == nullptr) return;
                for(std::string s : separator) std::cout << s;
                std::cout << itm; separator.push_back(sep);
                exprC->accept_r(*this);
                separator.pop_back();
            }
            
            void visit_x(
                const ExprC *exprC, 
                std::string itm, 
                std::string sep) const
            {
                if(exprC == nullptr) return;
                for(std::string s : separator) std::cout << s;
                std::cout << itm; separator.push_back(sep);
                exprC->accept_x(*this);
                separator.pop_back();
            }
    };
}

#endif
