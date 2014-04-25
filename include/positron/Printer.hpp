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

#ifndef HPP_POSITRON_PRINTER_DEFINED
#define HPP_POSITRON_PRINTER_DEFINED

// Default libraries
#include <string>
#include <iostream>

// Libraries
#include "Syntax_C.hpp"

namespace positron
{
    class Printer : public Visitor
    {
        private:
            mutable std::vector<std::string> separator {};
            
        public:
            void visit(const intC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << dynamic_cast<const intC *>(exprC)->get();
                std::cout << std::endl;
            }
            
            void visit(const floatC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << dynamic_cast<const floatC *>(exprC)->get();
                std::cout << std::endl;
            }
            
            void visit(const varC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << dynamic_cast<const varC *>(exprC)->get();
                std::cout << std::endl;
            }
            
            void visit(const stringC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << dynamic_cast<const stringC *>(exprC)->get();
                std::cout << std::endl;
            }
            
            void visit(const lamC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "lamC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const plusC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "plusC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const bminusC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "bminusC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const multC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "multC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const divC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "divC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const modC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "modC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const eqC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "eqC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const neC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "neC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const ltC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "ltC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const leC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "leC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const gtC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "gtC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const geC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "geC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const ifC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "ifC" << std::endl;
                if(exprC->has_r())
                {
                    visit_l(exprC, "|- ", "|  "); 
                    if(exprC->has_x())
                    {
                        visit_r(exprC, "|- ", "|  ");
                        visit_x(exprC, "'- ", "   ");
                    }
                    else visit_r(exprC, "'- ", "   ");
                }
            }
            
            void visit(const seqC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "seqC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const setC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "setC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
            }
            
            void visit(const storeC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "storeC" << std::endl;
                visit_l(exprC, "'- ", "   ");
            }
            
            void visit(const fetchC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "fetchC" << std::endl;
                visit_l(exprC, "'- ", "   ");
            }
            
            void visit(const printC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "printC" << std::endl;
                visit_l(exprC, "'- ", "   ");
            }
            
            void visit(const appC *exprC) const 
            {
                if(exprC == nullptr) return;
                std::cout << "appC" << std::endl;
                visit_l(exprC, "|- ", "|  "); 
                visit_r(exprC, "'- ", "   ");
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
