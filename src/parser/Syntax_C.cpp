#include <iostream>
#include "Syntax_C.hpp"
using namespace parser;

void numC::print(int n_spaces, char sep) const
{
    std::cout << this->n << std::endl;
}

void numC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void plusC::print(int n_spaces, char sep) const
{
    std::cout << "plusC" << std::endl;

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "|- "; sons[0]->print(n_spaces+1, '|');

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "'- "; sons[1]->print(n_spaces+1, ' ');
}

void plusC::accept(const Visitor& visitor) const
{
    for(const ExprC *son : sons)
        son->accept(visitor);
    visitor.visit(this);
}

void multC::print(int n_spaces, char sep) const
{
    std::cout << "multC" << std::endl;

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "|- "; sons[0]->print(n_spaces+1, '|');

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "'- "; sons[1]->print(n_spaces+1, ' ');
}

void multC::accept(const Visitor& visitor) const
{
    for(const ExprC *son : sons)
        son->accept(visitor);
    visitor.visit(this);
}

void ifC::print(int n_spaces, char sep) const
{
    std::cout << "ifC" << std::endl;

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "|- if"; sons[0]->print(n_spaces+1, '|');

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    
    std::cout << "|- "; sons[1]->print(n_spaces+1, '|');

    for(int i = 0; i < n_spaces; i++) std::cout << sep << "  ";
    std::cout << "'- "; sons[2]->print(n_spaces+1, ' ');
}

void ifC::accept(const Visitor& visitor) const
{
    sons[0]->accept(visitor);
    visitor.visit(this);
    sons[1]->accept(visitor);
    sons[2]->accept(visitor);
}

std::ostream& parser::operator<<(std::ostream& os, const ExprC& exprC)
{
    exprC.print(0, ' ');
    return os;
}
