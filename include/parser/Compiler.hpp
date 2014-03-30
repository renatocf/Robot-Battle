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

#ifndef HPP_PARSER_COMPILER_DEFINED
#define HPP_PARSER_COMPILER_DEFINED

// Default libraries
#include <memory>

// Libraries
#include "Command.hpp"
#include "Desugar.hpp"
#include "Syntax_C.hpp"
#include "Syntax_S.hpp"
#include "Syntax2Asm.hpp"

namespace parser
{
    class Compiler
    {
        public:
            vm::Prog compile(const ExprC *root) const
            {
                Syntax2Asm visitor {};
                root->accept(visitor);
                vm::Prog prog { std::move(visitor.get()) };
                prog.push_back(vm::Command { vm::Command::Opcode::PRN });
                prog.push_back(vm::Command { vm::Command::Opcode::END });
                return prog;
            }
            
            vm::Prog compile(const ExprC& root) const
            {
                return compile(&root);
            }
            
            vm::Prog compile(const ExprS& root) const
            {
                return compile(&root);
            }
            
            vm::Prog compile(const ExprS *root) const
            {
                std::shared_ptr<ExprC> core { Desugar{}.desugar(root) };
                vm::Prog prog { compile(core.get()) };
                return prog;
            }
    };
}

#endif
