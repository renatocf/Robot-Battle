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

#ifndef HPP_OPTIONS_OPTIONS_DEFINED
#define HPP_OPTIONS_OPTIONS_DEFINED

/**
 * @file  Options.hpp
 * @brief Define options to be used in the game.
 */

// C Libraries
#include <getopt.h>

/**
 * @namespace Options
 * @brief All functions and variables related to Game options.
 *
 * Define the prototype to a function to parse arguments and 
 * set variables to be used in this game.
 */
namespace Options 
{
    /**
     * @brief Parse arguments came from the command line.
     * 
     * Set game options and flags, using as background 
     * the getopt.h package.
     * 
     * @param argc Number of arguments in the command line
     * @param argv Array of string with the arguments
     */
    void parse_args(int argc, char **argv);
}

#endif
