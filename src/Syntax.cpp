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

/** 
 * @file  Syntax.cpp
 * @brief Tester for the Syntax tree while it is not integrated
 */

// Default libraries
#include <iostream>
#include <stdexcept>
using namespace std;

// Libraries
#include "RVM.hpp"
#include "Options.hpp"

#include "Desugar.hpp"
#include "Syntax_C.hpp"
#include "Syntax_S.hpp"
#include "Compiler.hpp"

/**
 * @fn Main function.
 * @param  argc Number of arguments in the command line
 * @param  argv Array of string with the arguments
 * @return 0 if success; non-zero otherwise
 */
int main(int argc, char **argv)
{
    // Process options
    Options::parse_args(argc, argv);
    
    // Usage
    if(optind <= argc && argc-optind != 0)
    {
        cout << "USAGE: Syntax" << endl;
        return 0;
    }
    
    using namespace parser;
    /* vm::RVM{ Compiler{}.compile(plusC { numC{2}, numC{2} }) }.run(); */
    // cout << Compiler{}.compile(
    //     ifC { numC{1},
    //         plusC { numC{2}, numC{2} },
    //         plusC { numC{3}, numC{3} },
    //     }) 
    // << endl;
    
    // cout << Desugar{}.desugar(ifS{numS{1},numS{2},numS{3}});
    
    ExprS *tree = new uminusS{ new numS{5} };
    vm::Prog prog { Compiler{}.compile(tree) };
    cout << prog << endl;
    vm::RVM{ prog }.run();
    delete tree;
    
    // vm::Prog minus { Compiler{}.compile(bminusC{numC{2},numC{1}}) };
    // cout << minus << endl;
    // vm::RVM{ minus }.run();
    
    // cout << ifC{numC{1},plusC{numC{2},numC{2}},numC{3}} << endl;
    // cout << ifC{numC{1},ifC{numC{0},numC{1},numC{2}},numC{3}} << endl; 
    // vm::Prog ifelse { Compiler{}.compile(
        // ifC{numC{1},ifC{numC{0},numC{1},numC{2}},numC{3}}
    // ) };
    // cout << ifelse << endl;
    // vm::RVM{ ifelse }.run();
    
    // vm::Prog test { Compiler{}.compile(plusC{numC{2},numC{2}}) };
    // cout << test << endl;
    // vm::RVM{ test }.run();
    
    return 0;
}
