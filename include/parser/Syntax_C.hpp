#ifndef HPP_SYNTAX_C_DEFINED
#define HPP_SYNTAX_C_DEFINED

// Default libraries
#include <vector>
#include <typeinfo>
#include <iostream>

namespace parser
{
    class ExprC
    {
        protected:
            enum class Type { numC, plusC, multC, ifC };
            std::vector<const ExprC *> sons;
            
        public:
            const Type type;

            virtual void 
            print(int n_spaces, char sep) const = 0;
            
            virtual const std::vector<const ExprC *>& 
            get() const { return sons; }
    
            virtual void 
            accept(const class Visitor& visitor) const = 0;
             
        protected:
            ExprC(Type t, std::vector<const ExprC *> sons = {}) 
                : sons{sons}, type{t} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ExprC& exprC);
    };
    
    std::ostream& operator<<(std::ostream& os, const ExprC& exprC);
    
    class plusC : public ExprC
    {
        public:
            plusC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Type::plusC, {&l,&r}} {}
            
            void print  (int n_spaces, char sep) const;
            void accept (const Visitor& visitor) const;
    };
    
    class multC : public ExprC
    {
        public:
            multC(const ExprC& l, const ExprC& r)
                : ExprC{ExprC::Type::multC, {&l,&r}} {}
            
            void print  (int n_spaces, char sep) const;
            void accept (const Visitor& visitor) const;
    };
    
    class ifC : public ExprC
    {
        public:
            ifC(const ExprC& cond, const ExprC& yes, const ExprC& no)
                : ExprC{ExprC::Type::ifC, {&cond,&yes,&no}} {}

            void print  (int n_spaces, char sep) const;
            void accept (const Visitor& visitor) const;
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

            long long get_content() const { return this->n; }

            void print  (int n_spaces, char sep) const;
            void accept (const Visitor& visitor) const;
    };
    
    class Visitor
    {
        public:
            virtual void visit(const numC  *exprC) const = 0;
            virtual void visit(const plusC *exprC) const = 0;
            virtual void visit(const multC *exprC) const = 0;
            virtual void visit(const ifC   *exprC) const = 0;
    };
}

#endif
