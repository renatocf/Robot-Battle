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

#ifndef HPP_POSITRON_SYMBOL_TABLE_DEFINED
#define HPP_POSITRON_SYMBOL_TABLE_DEFINED

// Default libraries
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

// Libraries
#include "Syntax_C.hpp"
#include "Result.hpp"

namespace positron 
{
    using Symbol   = std::string;
    using Location = unsigned int;
    using Env = std::vector<std::unordered_map< Symbol,Location >>;
    
    class Result { protected: virtual ~Result() {}; };
    
    class intV  : public Result
    {
        private:
            int n;
        public:
            intV(int n = {}) : n{n} {}
            int get() const { return this->n; }
    };
    
    class floatV  : public Result
    {
        private:
            float f; 
        public:
            floatV(float f = {}) : f{f} {}
            float get() const { return this->f; }
    };
    
    class stringV  : public Result
    {
        private:
            std::string s; 
        public:
            stringV(std::string s = {}) : s{s} {}
            std::string get() const { return this->s; }
    };
    
    class closV : public Result
    {
        private:
            const lamC *lambda; Env env;
        public:
            closV(const lamC *lambda, const Env& env) 
                : Result{}, lambda{lambda}, env{env} {}
            
            const lamC *get_lam () const { return this->lambda; }
            Env         get_env () const { return this->env;    }
            
            ~closV() {}
    };
    
    class Symbol_table : public Visitor
    {
        private:
            mutable Env *env    = new Env{};
            mutable Result *res {};
            
            const ExprC *app;
            mutable ExprC *aux;
            mutable bool in_appC;
            mutable bool in_lamC;
            
            Location new_loc() const
            {
                static Location loc = 0;
                return loc++;
            }
            
            void bind(Symbol id, Location arg) const
            {
                env->back()[id] = arg;
            }
            
            Location lookup(std::string name) const
            {
                for(auto rit = env->rbegin(); rit != env->rend(); rit++)
                    if(rit->count(name)) return (*rit)[name];
                return 0; // TODO: throw exception
            }
        
        public:
            const ExprC *get() const
            {
                return aux;
            }
            
            void visit(const varC *exprC) const
            {
                std::string var { 
                    dynamic_cast<const varC *>(exprC)->get()
                };
                int pos = static_cast<int>(lookup(var));
                aux = new fetchC{ new intC{pos} };
                
                for(auto& v : *env)
                    for(auto& a : v)
                        std::cerr << a.first << " " << a.second << std::endl;
            }
            
            void visit(const intC    *exprC) const 
            { aux = new intC{*exprC}; }
            
            void visit(const floatC  *exprC) const 
            { aux = new floatC{*exprC}; }
            
            void visit(const stringC *exprC) const 
            { aux = new stringC{*exprC}; }
            
            void visit(const lamC *exprC) const 
            {
                // std::cerr << "In lamC" << std::endl;
                // if(env == nullptr) 
                //     std::cerr << "    env is null" << std::endl;
                // else
                //     std::cerr << "    env is not null" << std::endl;
                // b_operator(exprC);
                
                for(auto& v : *env)
                    for(auto& a : v)
                        std::cerr << a.first << " " << a.second << std::endl;
                
                res = new closV{ exprC, *env };
                if(res == nullptr)
                    std::cerr << "    res is null" << std::endl;
                else
                    std::cerr << "    res is not null" << std::endl;
            }
            
            void visit(const plusC *exprC) const 
            { b_operator(exprC); }
            
            void visit(const bminusC *exprC) const 
            { b_operator(exprC); }
            
            void visit(const multC *exprC) const
            { b_operator(exprC); }
            
            void visit(const divC *exprC) const
            { b_operator(exprC); }
            
            void visit(const modC *exprC) const
            { b_operator(exprC); }
            
            void visit(const eqC *exprC) const
            { b_operator(exprC); }
            
            void visit(const neC *exprC) const
            { b_operator(exprC); }
            
            void visit(const ltC *exprC) const
            { b_operator(exprC); }
            
            void visit(const leC *exprC) const
            { b_operator(exprC); }
            
            void visit(const gtC *exprC) const
            { b_operator(exprC); }
            
            void visit(const geC *exprC) const
            { b_operator(exprC); }
            
            void visit(const ifC *exprC) const
            { t_operator(exprC); }
            
            void visit(const seqC *exprC) const
            { b_operator(exprC); }
            
            void visit(const setC *exprC) const
            {  
                exprC->accept_r(*this);
                exprC->accept_l(*this);
            }
            
            void visit(const storeC *exprC) const
            {
                // Should never get here...
                std::cerr << __FILE__ << __LINE__ << ":";
                std::cerr << "Should never get here" << std::endl;
            }
            
            void visit(const fetchC *exprC) const
            {
                // Should never get here...
                std::cerr << __FILE__ << __LINE__ << ":";
                std::cerr << "Should never get here" << std::endl;
            }
            
            void visit(const printC *exprC) const
            { u_operator(exprC); }
            
            void visit(const appC    *exprC) const 
            {
                std::cerr << "===================" << std::endl;
                std::cerr << "In appC" << std::endl;
                std::cerr << exprC << std::endl;
                exprC->accept_l (*this); // Get closure
                
                std::cerr << "Cast closure" << std::endl;
                std::cerr << "    res is " << (res ? "" : "not") 
                          << "null" << std::endl;
                closV *closure  { dynamic_cast<closV *>(res) };
                if(closure == nullptr)
                    std::cerr << "    closure is null" << std::endl;
                
                const lamC *lam { closure->get_lam()         };
                
                std::cerr << "Before accept:" << std::endl;
                std::cerr << exprC->r << std::endl;
                exprC->accept_r(*this); // Interp argument
                std::cerr << aux << std::endl;
                
                std::cerr << "After accept:" << std::endl;
                closV *closure2 { dynamic_cast<closV *>(res) };
                const ExprC *arg { closure2->get_lam() };
                
                env->push_back({});     // Start extend-env
                std::cerr << "Env depth: " << env->size() << std::endl;
                
                std::cerr << "Creating new binding" << std::endl;
                Location pos = new_loc();
                bind(dynamic_cast<const varC *>(lam->l)->get(), pos);
                for(auto& pair : env->back())
                {
                    std::cerr << pair.first << ":" << pair.second;
                    std::cerr << std::endl;
                }
                
                std::cerr << "Interpret lambda" << std::endl;
                lam->r->accept(*this);     // Interp lambda 
                const ExprC *lam_body { aux };
                env->pop_back();           // Our scope is ended
                
                aux = new appC {
                    new lamC{new storeC{new intC{static_cast<int>(pos)}},lam_body}, arg };
            }
        
        private:
            template<typename T>
            void u_operator(const T *exprC) const
            {
                exprC->accept_l(*this); 
                const ExprC *l { exprC->has_l() ? aux : nullptr };
                aux = new T {l};
            }
            
            template<typename T>
            void b_operator(const T *exprC) const
            {
                std::cerr << "Env depth: " << env->size() << std::endl;
                exprC->accept_l(*this);
                const ExprC *l { exprC->has_l() ? aux : nullptr };
                exprC->accept_r(*this);
                const ExprC *r { exprC->has_r() ? aux : nullptr };
                aux = new T {l,r};
            }
            
            template<typename T>
            void t_operator(const T *exprC) const
            {
                exprC->accept_l(*this);
                const ExprC *l { exprC->has_l() ? aux : nullptr };
                exprC->accept_r(*this);
                const ExprC *r { exprC->has_r() ? aux : nullptr };
                exprC->accept_x(*this);
                const ExprC *x { exprC->has_x() ? aux : nullptr };
                aux = new T {l,r,x};
            }
    };
}

#endif
