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
#include <iostream>

// Libraries
#include "Debug.hpp"
#include "Options.hpp"
using namespace Options;

void Options::parse_args(int argc, char **argv)
{
    static struct option long_options[] = {
        { "debug", no_argument, NULL, 'd' },
        { "help" , no_argument, NULL, 'h' },
        { 0, 0, 0, 0 }
    };
    
    int option_index = 0; int c;
    while((c = getopt_long(argc, argv, "d",
               long_options, &option_index)) != -1)
    {
        switch(c) 
        {
            case 'd':
                vm::Debug::OFF = false;
                break;
            case 'h':
                break;
            case '?':
                break;
            default:
                std::cout << "?? getopt returned character code 0" << c << " ??" << std::endl;
        }
    }
}
