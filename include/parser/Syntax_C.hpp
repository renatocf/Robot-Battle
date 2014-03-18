#ifndef HPP_SYNTAX_C_DEFINED
#define HPP_SYNTAX_C_DEFINED

// Default libraries
#include <vector>
#include <typeinfo>
#include <iostream>

// Libraries
// #include "Visitor.hpp"

namespace parser
{
    
    class ExprC
    {
        protected:
            enum class Type { numC, plusC, multC };
            std::vector<const ExprC *> sons;
            
        public:
            const Type type;

            virtual void 
            print(int n_spaces, char sep) const = 0;
            
            virtual const std::vector<const ExprC *>& 
            get() const { return sons; }
            
            class Visitor
            {
                public:
                    virtual void visit(const ExprC *exprC) const {}
            };
            
            virtual void
            visit(const ExprC::Visitor& visitor) { visitor.visit(this); }
             
        protected:
            ExprC(Type t) : type{t} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ExprC& exprC);
            
        friend class Compiler;
    };
    
    std::ostream& operator<<(std::ostream& os, const ExprC& exprC);
    
    class plusC : public ExprC
    {
        public:
            plusC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Type::plusC}
            {
                sons.push_back(&l); sons.push_back(&r);
            }
            
            void print(int n_spaces, char sep) const
            {
                std::cout << "plusC" << std::endl;

                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "|- "; sons[0]->print(n_spaces+1, '|');

                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "'- "; sons[1]->print(n_spaces+1, ' ');
            }
    };
    
    class multC : public ExprC
    {
        public:
            multC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Type::multC}
            {
                sons.push_back(&l); sons.push_back(&r);
            }
            
            void print(int n_spaces, char sep) const
            {
                std::cout << "multC" << std::endl;

                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "|- "; sons[0]->print(n_spaces+1, '|');

                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "'- "; sons[1]->print(n_spaces+1, ' ');
            }
    };
    
    class numC : public ExprC
    {
        private:
            long long n; 
         
        public:
            numC(int n)
                : ExprC{ExprC::Type::numC}, n{n} {}
            numC(long long n)
                : ExprC{ExprC::Type::numC}, n{n} {}
            
            void print(int n_spaces, char sep) const
            {
                std::cout << this->n << std::endl;
            }
            
            long long get_content() const { return this->n; }
    };
}

#endif
