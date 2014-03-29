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

#ifndef HPP_SYNTAX_C_DEFINED
#define HPP_SYNTAX_C_DEFINED

// Default libraries
#include <vector>

namespace parser
{
    class ExprC
    {
        protected:
            enum class Core { numC, plusC, bminusC, multC, divC, ifC };
            const ExprC *l; const ExprC *r; const ExprC *x;
            
        public:
            const Core type;
            
            virtual void 
            accept(const class Visitor& visitor) const = 0;
            
            void accept_l(const Visitor& visitor) const
            { l->accept(visitor); }
            
            void accept_r(const Visitor& visitor) const
            { r->accept(visitor); }
            
            void accept_x(const Visitor& visitor) const
            { x->accept(visitor); }
            
        protected:
            ExprC(Core t, 
                const ExprC *l = {}, 
                const ExprC *r = {},
                const ExprC *x = {}
            ) 
                : l{l}, r{r}, x{x}, type{t} {}
            
            virtual ~ExprC() {};
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ExprC& exprC);
    };
    
    std::ostream& operator<<(std::ostream& os, const ExprC& exprC);
    
    class plusC : public ExprC
    {
        public:
            plusC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Core::plusC, &l, &r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class bminusC : public ExprC
    {
        public:
            bminusC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Core::bminusC, &l, &r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class multC : public ExprC
    {
        public:
            multC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Core::multC, &l, &r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class divC : public ExprC
    {
        public:
            divC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Core::divC, &l, &r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class ifC : public ExprC
    {
        public:
            ifC(const ExprC& cond, const ExprC& yes)
                : ExprC{ExprC::Core::ifC, &cond, &yes} {}
            ifC(const ExprC& cond, const ExprC& yes, const ExprC& no)
                : ExprC{ExprC::Core::ifC, &cond, &yes, &no} {}

            void accept (const Visitor& visitor) const;
    };
    
    class numC : public ExprC
    {
        private:
            long long n; 

        public:
            numC(int n)
                : ExprC{ExprC::Core::numC}, n{n} {}
            numC(long long n)
                : ExprC{ExprC::Core::numC}, n{n} {}
            
            long long get_content() const { return this->n; }
            
            void accept (const Visitor& visitor) const;
    };
    
    class Visitor
    {
        public:
            virtual void visit(const numC    *exprC) const = 0;
            virtual void visit(const plusC   *exprC) const = 0;
            virtual void visit(const bminusC *exprC) const = 0;
            virtual void visit(const multC   *exprC) const = 0;
            virtual void visit(const divC    *exprC) const = 0;
            virtual void visit(const ifC     *exprC) const = 0;
    };
}

#endif
