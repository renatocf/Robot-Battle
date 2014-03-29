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
 * @file  Main.cpp
 * @brief Main function, which start the program
 */

// Default libraries
#include <iostream>
#include <stdexcept>
using namespace std;

// Libraries
#include "RVM.hpp"
#include "Quark.hpp"
#include "Command.hpp"
#include "Options.hpp"
#include "Stackable.hpp"

#include "Syntax_C.hpp"
#include "Compiler.hpp"
#include "SyntaxC2Asm.hpp"

/**
 * @fn Main function.
 * @param  argc Number of arguments in the command line
 * @param  argv Array of string with the arguments
 * @return 0 if success; non-zero otherwise
 */
int main(int argc, char **argv)
{
    using namespace parser;
    
    // Process options
    Options::parse_args(argc, argv);
    
    // // Usage
    // if(optind <= argc && argc-optind != 1)
    // {
    //     cout << "USAGE: Main Program_name" << endl;
    //     return 0;
    // }
    // 
    // try {
    //     parser::quark::Func_ptr upload 
    //         = parser::quark::functions.at(argv[optind]);
    //     
    //     vm::RVM Bender { upload() };
    //     Bender.run();
    //     
    // } catch (const std::out_of_range& exc) {
    //     cerr << "ERROR: Program \"" << argv[1] << "\" unknown." << endl;
    //     return -1;
    // }
    
    // vm::Prog minus { Compiler{}.compile(bminusC{numC{2},numC{1}}) };
    // cout << minus << endl;
    // vm::RVM{ minus }.run();
    
    vm::Prog ifelse { Compiler{}.compile(ifC{numC{1},numC{2},numC{3}}) };
    cout << ifelse << endl;
    vm::RVM{ ifelse }.run();
    
    // vm::Prog test { Compiler{}.compile(plusC{numC{2},numC{2}}) };
    // cout << test << endl;
    // vm::RVM{ test }.run();
    
    return 0;
}
