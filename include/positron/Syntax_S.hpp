/**********************************************************************/
/* Sopyright 2014 RSF                                                 */
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in compliance with the License.   */
/* You may obtain a copy of the License at                            */
/*                                                                    */
/*     http://www.apache.org/licenses/LISENSE-2.0                     */
/*                                                                    */
/* Unless required by applicable law or agreed to in writing,         */
/* software distributed under the License is distributed on an        */
/* "AS IS" BASIS, WITHOUT WARRANTIES OR SONDITIONS OF ANY KIND,       */
/* either express or implied.                                         */
/* See the License for the specific language governing permissions    */
/* and limitations under the License.                                 */
/**********************************************************************/

#ifndef HPP_POSITRON_SYNTAX_S_DEFINED
#define HPP_POSITRON_SYNTAX_S_DEFINED

// Default libraries
#include <string>

namespace positron
{
    struct ExprS
    {
        protected:
            enum class Sugar { 
                intS, floatS, idS,
                plusS, bminusS, multS, divS, modS,
                ifS, seqS, printS, lamS, appS,
                uminusS
            };
            const ExprS *l; const ExprS *r; const ExprS *x;
            
        public:
            const Sugar type;
            
            virtual ~ExprS()
            { 
                if(l) delete l; 
                if(r) delete r; 
                if(x) delete x; 
            }
            
        protected:
            ExprS(Sugar t, 
                const ExprS *l = {}, 
                const ExprS *r = {},
                const ExprS *x = {}
            )
                : l{l}, r{r}, x{x}, type{t} {}
        
        friend class Desugar;
    };
    
    class intS : public ExprS
    {
        private:
            int n {}; 

        public:
            intS(int n)
                : ExprS{ExprS::Sugar::intS}, n{n} {}
            
            int get() const { return this->n; }
    };
    
    class floatS : public ExprS
    {
        private:
            float n {}; 

        public:
            floatS(float n)
                : ExprS{ExprS::Sugar::floatS}, n{n} {}
            
            float get() const { return this->n; }
    };
    
    class idS : public ExprS
    {
        private:
            std::string name {};

        public:
            idS(const std::string& name)
                : ExprS{ExprS::Sugar::idS}, name{name} {}
            
            std::string get() const { return name; }
    };
    
    struct lamS : public ExprS
    {
        lamS(const idS *var, const ExprS *body)
            : ExprS{ExprS::Sugar::lamS, var, body} {}
    };
    
    struct plusS : public ExprS
    {
        plusS(const ExprS *l, const ExprS *r)
            : ExprS{ExprS::Sugar::plusS, l, r} {}
    };
    
    struct bminusS : public ExprS
    {
        bminusS(const ExprS *l, const ExprS *r)
            : ExprS{ExprS::Sugar::bminusS, l, r} {}
    };
    
    struct multS : public ExprS
    {
        multS(const ExprS *l, const ExprS *r)
            : ExprS{ExprS::Sugar::multS, l, r} {}
    };
    
    struct divS : public ExprS
    {
        divS(const ExprS *l, const ExprS *r)
            : ExprS{ExprS::Sugar::divS, l, r} {}
    };
    
    struct modS : public ExprS
    {
        modS(const ExprS *l, const ExprS *r)
            : ExprS{ExprS::Sugar::modS, l, r} {}
    };
    
    struct ifS : public ExprS
    {
        ifS(const ExprS *cond, const ExprS *yes)
            : ExprS{ExprS::Sugar::ifS, cond, yes} {}
        ifS(const ExprS *cond, const ExprS *yes, const ExprS *no)
            : ExprS{ExprS::Sugar::ifS, cond, yes, no} {}
    };
    
    struct seqS : public ExprS
    {
        seqS(const ExprS *first, const ExprS *second)
            : ExprS{ExprS::Sugar::seqS, first, second} {}
    };
    
    struct printS : public ExprS
    {
        printS(const ExprS *string)
            : ExprS{ExprS::Sugar::printS, string} {}
    };
    
    struct appS : public ExprS
    {
        appS(const ExprS *cond, const ExprS *yes)
            : ExprS{ExprS::Sugar::appS, cond, yes} {}
    };
    
    struct uminusS : public ExprS
    {
        uminusS(const ExprS *l)
            : ExprS{ExprS::Sugar::uminusS, l} {}
    };
}

#endif
