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

#ifndef HPP_POSITRON_SYNTAX_C_DEFINED
#define HPP_POSITRON_SYNTAX_C_DEFINED

// Default libraries
#include <vector>
#include <string>
#include <iostream>

namespace positron
{
    class ExprC
    {
        protected:
            enum class Core { 
                intC, floatC, idC, 
                plusC, bminusC, multC, divC, modC,
                eqC, neC, gtC, geC, ltC, leC,
                ifC, seqC,
                printC, 
                lamC, appC
            };
            const ExprC *l; const ExprC *r; const ExprC *x;
            
        public:
            const Core type;
            
            virtual void 
            accept(const class Visitor& visitor) const = 0;
            
            bool has_l() const { return l; }
            bool has_r() const { return r; }
            bool has_x() const { return x; }
            
            void accept_l(const Visitor& visitor) const
            { if(l) l->accept(visitor); }
            
            void accept_r(const Visitor& visitor) const
            { if(r) r->accept(visitor); }
            
            void accept_x(const Visitor& visitor) const
            { if(x) x->accept(visitor); }
            
            virtual ~ExprC()
            { 
                if(l) delete l; 
                if(r) delete r; 
                if(x) delete x; 
            }
            
        protected:
            ExprC(Core t, 
                const ExprC *l = {}, 
                const ExprC *r = {},
                const ExprC *x = {}
            ) 
                : l{l}, r{r}, x{x}, type{t} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ExprC& exprC);
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ExprC *exprC);
    };
    
    std::ostream& operator<<(std::ostream& os, const ExprC& exprC);
    std::ostream& operator<<(std::ostream& os, const ExprC *exprC);
    
    class intC : public ExprC
    {
        private:
            int n; 
            
        public:
            intC(int n)
                : ExprC{ExprC::Core::intC}, n{n} {}
            
            int get() const { return this->n; }
            
            void accept (const Visitor& visitor) const;
    };
    
    class floatC : public ExprC
    {
        private:
            float n; 
            
        public:
            floatC(float n)
                : ExprC{ExprC::Core::floatC}, n{n} {}
            
            float get() const { return this->n; }
            
            void accept (const Visitor& visitor) const;
    };
    
    class idC : public ExprC
    {
        private:
            std::string name;
            
        public:
            idC(std::string name)
                : ExprC{ExprC::Core::idC}, name{name} {}
            
            std::string get() const { return this->name; }
            
            void accept (const Visitor& visitor) const;
    };
    
    class lamC : public ExprC
    {
        public:
            lamC(const idC *var, const ExprC *body)
                : ExprC{ExprC::Core::lamC, var, body} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class plusC : public ExprC
    {
        public:
            plusC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::plusC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class bminusC : public ExprC
    {
        public:
            bminusC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::bminusC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class multC : public ExprC
    {
        public:
            multC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::multC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class divC : public ExprC
    {
        public:
            divC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::divC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class modC : public ExprC
    {
        public:
            modC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::modC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class eqC : public ExprC
    {
        public:
            eqC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::eqC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class neC : public ExprC
    {
        public:
            neC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::neC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class ltC : public ExprC
    {
        public:
            ltC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::ltC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class leC : public ExprC
    {
        public:
            leC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::leC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class gtC : public ExprC
    {
        public:
            gtC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::gtC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class geC : public ExprC
    {
        public:
            geC(const ExprC *l, const ExprC *r)
                : ExprC{ExprC::Core::geC, l, r} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class ifC : public ExprC
    {
        public:
            ifC(const ExprC *cond, 
                const ExprC *y, const ExprC *n = nullptr)
                : ExprC{ExprC::Core::ifC, cond, y, n} {}

            void accept (const Visitor& visitor) const;
    };
    
    class seqC : public ExprC
    {
        public:
            seqC(const ExprC *first, const ExprC *second)
                : ExprC{ExprC::Core::seqC, first, second} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class printC : public ExprC
    {
        public:
            printC(const ExprC *l)
                : ExprC{ExprC::Core::printC, l} {}
            
            void accept (const Visitor& visitor) const;
    };
    
    class appC : public ExprC
    {
        public:
            appC(const ExprC *lam, const ExprC *arg)
                : ExprC{ExprC::Core::appC, lam, arg} {}

            void accept (const Visitor& visitor) const;
    };
    
    class Visitor
    {
        public:
            virtual void visit(const intC    *exprC) const = 0;
            virtual void visit(const floatC  *exprC) const = 0;
            virtual void visit(const idC     *exprC) const = 0;
            virtual void visit(const plusC   *exprC) const = 0;
            virtual void visit(const bminusC *exprC) const = 0;
            virtual void visit(const multC   *exprC) const = 0;
            virtual void visit(const divC    *exprC) const = 0;
            virtual void visit(const modC    *exprC) const = 0;
            virtual void visit(const eqC     *exprC) const = 0;
            virtual void visit(const neC     *exprC) const = 0;
            virtual void visit(const ltC     *exprC) const = 0;
            virtual void visit(const leC     *exprC) const = 0;
            virtual void visit(const gtC     *exprC) const = 0;
            virtual void visit(const geC     *exprC) const = 0;
            virtual void visit(const ifC     *exprC) const = 0;
            virtual void visit(const seqC    *exprC) const = 0;
            virtual void visit(const printC  *exprC) const = 0;
            virtual void visit(const lamC    *exprC) const = 0;
            virtual void visit(const appC    *exprC) const = 0;
    };
}

#endif
