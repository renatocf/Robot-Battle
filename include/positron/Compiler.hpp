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
                                                      
#ifndef HPP_POSITRON_COMPILER_DEFINED
#define HPP_POSITRON_COMPILER_DEFINED

// Default libraries
#include <string>

// Libraries
#include "Int.hpp"
#include "Text.hpp"
#include "Float.hpp"
#include "Command.hpp"
#include "Syntax_C.hpp"

namespace positron
{
    class Compiler : public Visitor
    {
        private:
            mutable vm::Prog prog {};
            mutable unsigned int c_if = 0;
            
        public:
            const vm::Prog get() const
            {
                return prog;
            }
            
            void visit(const intC    *exprC) const;
            void visit(const floatC  *exprC) const;
            void visit(const idC     *exprC) const;
            void visit(const stringC *exprC) const;
            void visit(const lamC    *exprC) const;
            
            void visit(const plusC   *exprC) const;
            void visit(const bminusC *exprC) const;            
            void visit(const multC   *exprC) const;
            void visit(const divC    *exprC) const;
            void visit(const modC    *exprC) const;
            
            void visit(const eqC     *exprC) const;
            void visit(const neC     *exprC) const;
            void visit(const ltC     *exprC) const;
            void visit(const leC     *exprC) const;
            void visit(const gtC     *exprC) const;
            void visit(const geC     *exprC) const;
            
            void visit(const ifC     *exprC) const;
            void visit(const seqC    *exprC) const;
            void visit(const appC    *exprC) const;
            
            void visit(const printC  *exprC) const;
            
    };
}

#endif
