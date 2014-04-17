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
 * @file  simulator.cpp
 * @brief Simulator for tests with different arenas
 */

// Default libraries
#include <iostream>
#include <stdexcept>
using namespace std;

// Libraries
#include "Map.hpp"
#include "RVM.hpp"
#include "Options.hpp"

#include<vector>

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
        cout << "USAGE: simulator" << endl;
        return 0;
    }
    
    using namespace arena;
    arena::Map map {{
        { Terrain{1}, Terrain{1}, Terrain{1} },
        { Terrain{1}, Terrain{1}, Terrain{1} },
        { Terrain{1}, Terrain{1}, Terrain{1} },
    }};
    
    cout << map;
    
    return 0;
}
