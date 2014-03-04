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
 * Main class, which starts the program.
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

int main(int argc, char **argv)
{
    // Process options
    Options::parse_args(argc, argv);
    
    // Usage
    if(optind < argc && argc-optind != 1)
    {
        cout << "USAGE: Main Program_name" << endl;
        return 0;
    }
    
    try {
        parser::quark::Func_ptr upload 
            = parser::quark::functions.at(argv[optind]);
        
        vm::RVM Bender { upload() };
        Bender.run();
        
    } catch (const std::out_of_range& exc) {
        cerr << "ERROR: Program \"" << argv[1] << "\" unknown." << endl;
        return -1;
    }
    
    return 0;
}
