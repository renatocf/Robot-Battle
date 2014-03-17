#ifndef HPP_SYNTAX_C_DEFINED
#define HPP_SYNTAX_C_DEFINED

// Default libraries
#include <vector>
#include <typeinfo>
#include <iostream>

namespace parser
{
    class ArithC
    {   
        public:
            virtual void print(int n_spaces, char sep) const = 0;
        
        protected:
            enum class Type { numC, plusC, multC };
            Type type {};
            
            std::vector<const ArithC *> sons;
            
            ArithC(Type t) : type{t} {}
            
            friend std::ostream& 
            operator<<(std::ostream& os, const ArithC& arithC);
    };
    
    std::ostream& operator<<(std::ostream& os, const ArithC& arithC);
    
    class plusC : public ArithC
    {
        public:
            const ArithC *l, *r;
            
            plusC(const ArithC& l, const ArithC& r)
                : ArithC{ArithC::Type::plusC}, l{&l}, r{&r} {}
            
            void print(int n_spaces, char sep) const
            {
                std::cout << "plusC" << std::endl;
                
                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "|- "; l->print(n_spaces+1, '|');
                
                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "'- "; r->print(n_spaces+1, ' ');
            }
    };
    
    class multC : public ArithC
    {
        public:
            const ArithC *l, *r;
            
            void print(int n_spaces, char sep) const
            {
                std::cout << "multC" << std::endl;
                
                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "|- "; l->print(n_spaces+1, '|');
                
                for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
                std::cout << "'- "; r->print(n_spaces+1, ' ');
            }
        
            multC(const ArithC& l, const ArithC& r)
                : ArithC{ArithC::Type::multC}, l{&l}, r{&r} {}
    };
    
    class numC : public ArithC
    {
        public:
            long long n; 
            
            void print(int n_spaces, char sep) const
            {
                std::cout << this->n << std::endl;
            }
            
            numC(int n)
                : ArithC{ArithC::Type::numC}, n{n} {}
            numC(long long n)
                : ArithC{ArithC::Type::numC}, n{n} {}
    };
}

#endif
