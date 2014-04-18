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

#ifndef HPP_POSITRON_RPC_DEFINED
#define HPP_POSITRON_RPC_DEFINED

// Default libraries
#include <memory>
#include <string>
#include <fstream>

// Libraries
#include "Parser.ih"
#include "Syntax_S.hpp"
#include "Desugar.hpp"
#include "Syntax_C.hpp"
#include "Symbol_table.hpp"
#include "Compiler.hpp"
#include "Command.hpp"

namespace positron
{
    class RPC
    {
        public:
            vm::Prog compile(std::string filename) const
            {
                std::ifstream file { filename };
                
                // TODO: Throw exception
                if(!file) return vm::Prog{};
                
                // Scan and parse file
                Parser parser { file };
                parser.parse();
                
                return compile(parser.get_tree());
            }
            
            vm::Prog compile(const ExprS *root) const
            {
                if(root == nullptr) return vm::Prog{};
                std::shared_ptr<ExprC> core { Desugar{}.desugar(root) };
                vm::Prog prog { compile(core.get()) };
                return prog;
            }
            
            vm::Prog compile(const ExprS& root) const
            {
                return compile(&root);
            }
            
            vm::Prog compile(const ExprC *root) const
            {
                if(root == nullptr) return vm::Prog{};
                root->accept(Symbol_table{});
                Compiler compiler {};
                root->accept(compiler);
                vm::Prog prog { std::move(compiler.get()) };
                prog.push_back(vm::Command { vm::Command::Opcode::END });
                return prog;
            }
            
            vm::Prog compile(const ExprC& root) const
            {
                return compile(&root);
            }
    };
}

#endif
