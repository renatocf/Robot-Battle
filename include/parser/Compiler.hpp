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

// Libraries
#include "Command.hpp"
#include "Syntax_C.hpp"
#include "Syntax2Asm.hpp"

namespace parser
{
    class Compiler
    {
        public:
            vm::Prog compile(const ExprC& root)
            {
                return compile(&root);
            }
            
            vm::Prog compile(const ExprC *root)
            {
                Syntax2Asm visitor {};
                root->accept(visitor);
                vm::Prog prog { std::move(visitor.get()) };
                prog.push_back(vm::Command { vm::Command::Opcode::PRN });
                prog.push_back(vm::Command { vm::Command::Opcode::END });
                return prog;
            }
    };
}

#endif
