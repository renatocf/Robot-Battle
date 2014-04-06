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
 * @file  rpc.cpp
 * @brief Robot Positronic Compiler (RPC) for development phase.
 */

// Default libraries
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

// Libraries
#include "RVM.hpp"
#include "Parser.ih"
#include "Options.hpp"
#include "Compiler.hpp"

// Prototypes
void compile_and_run(const positron::Parser& parser);

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
    
    if(argc > 1)
    {
        for(int i = optind; i < argc; i++)
        {
            // Open file
            std::ifstream file      { argv[i] };
            
            if(!file) 
            {
                std::cerr << argv[i] << "not exists" << std::endl;
                file.close();
                continue;
            }
            
            std::cout << "Processing file " << argv[i] << std::endl;
            std::cout << "================" << std::endl << std::endl;
            
            // Create a non-iteractive parser
            positron::Parser parser { file };
            parser.parse();
            
            compile_and_run(parser);
        }
    }
    else 
    {
        // Create an iteractive parser
        while(1) 
        {
            std::cout << "> ";
            
            // Create new iteractive parser
            positron::Parser parser{};
            parser.parse();
            
            std::cout << std::endl;
            
            // If received <<EOF>>, stop
            if(!parser.get_tree()) break;
            else compile_and_run(parser);
        }
    }
    
    return 0;
}

void compile_and_run(const positron::Parser& parser)
{
    vm::Prog assembly {
        positron::Compiler{}.compile(parser.get_tree()) 
    };
    
    std::cout << "Compilation result: " << std::endl;
    std::cout << assembly << std::endl << std::endl;
    
    std::cout << "Program output: " << std::endl;
    vm::RVM{ assembly }.run();
    
    std::cout << std::endl;
}
