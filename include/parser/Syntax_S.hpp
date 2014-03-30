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

#ifndef HPP_PARSER_SYNTAX_S_DEFINED
#define HPP_PARSER_SYNTAX_S_DEFINED

namespace parser 
{
    struct ExprS
    {
        protected:
            enum class Sugar { numS, plusS, bminusS, multS, divS, ifS };
            const ExprS *l; const ExprS *r; const ExprS *x;
            
        public:
            const Sugar type;
            
        protected:
            ExprS(Sugar t, 
                const ExprS *l = {}, 
                const ExprS *r = {},
                const ExprS *x = {}
            )
                : l{l}, r{r}, x{x}, type{t} {}
            
            virtual ~ExprS() {};
        
        friend class Desugar;
    };
    
    struct plusS : public ExprS
    {
        plusS(const ExprS& l, const ExprS& r)
            : ExprS{ExprS::Sugar::plusS, &l, &r} {}
    };
    
    struct bminusS : public ExprS
    {
        bminusS(const ExprS& l, const ExprS& r)
            : ExprS{ExprS::Sugar::bminusS, &l, &r} {}
    };
    
    struct multS : public ExprS
    {
        multS(const ExprS& l, const ExprS& r)
            : ExprS{ExprS::Sugar::multS, &l, &r} {}
    };
    
    struct divS : public ExprS
    {
        divS(const ExprS& l, const ExprS& r)
            : ExprS{ExprS::Sugar::divS, &l, &r} {}
    };
    
    struct ifS : public ExprS
    {
        ifS(const ExprS& cond, const ExprS& yes)
            : ExprS{ExprS::Sugar::ifS, &cond, &yes} {}
        ifS(const ExprS& cond, const ExprS& yes, const ExprS& no)
            : ExprS{ExprS::Sugar::ifS, &cond, &yes, &no} {}
    };
    
    class numS : public ExprS
    {
        private:
            long long n; 

        public:
            numS(int n)
                : ExprS{ExprS::Sugar::numS}, n{n} {}
            numS(long long n)
                : ExprS{ExprS::Sugar::numS}, n{n} {}
            
            long long get() const { return this->n; }
    };
}

#endif
