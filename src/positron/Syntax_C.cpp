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

// Default libraries
#include "Syntax_C.hpp"
#include "Syntax2Stdout.hpp"
using namespace positron;

void intC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void floatC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void idC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

void lamC::accept(const Visitor& visitor) const
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

void appC::accept(const Visitor& visitor) const
{
    visitor.visit(this);
}

std::ostream& positron::operator<<(std::ostream& os, const ExprC& exprC)
{
    Syntax2Stdout printer {};
    exprC.accept(printer);
    return os;
}

std::ostream& positron::operator<<(std::ostream& os, const ExprC *exprC)
{
    Syntax2Stdout printer {};
    exprC->accept(printer);
    return os;
}
