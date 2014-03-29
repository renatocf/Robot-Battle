#include <iostream>
#include "SyntaxC2Print.hpp"
#include "Syntax_C.hpp"
using namespace parser;

void numC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void plusC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void bminusC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void multC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void divC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void ifC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

std::ostream& parser::operator<<(std::ostream& os, const ExprC& exprC)
{
    SyntaxC2Print printer {};
    exprC.accept(printer);
    return os;
}
