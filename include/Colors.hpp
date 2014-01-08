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

#ifndef HPP_COLORS_DEFINED
#define HPP_COLORS_DEFINED

// Windows environment
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string RESTORE = "";
static const std::string BLACK   = ""; // Black
static const std::string RED     = ""; // Red
static const std::string GREEN   = ""; // Green
static const std::string YELLOW  = ""; // Yellow
static const std::string BLUE    = ""; // Blue
static const std::string PURPLE  = ""; // Purple
static const std::string CYAN    = ""; // Cyan
static const std::string WHITE   = ""; // White

// Unix-alike
#else 
static const std::string RESTORE = "\033[0m";
static const std::string BLACK   = "\033[1;30m"; // Black
static const std::string RED     = "\033[1;31m"; // Red
static const std::string GREEN   = "\033[1;32m"; // Green
static const std::string YELLOW  = "\033[1;33m"; // Yellow
static const std::string BLUE    = "\033[1;34m"; // Blue
static const std::string PURPLE  = "\033[1;35m"; // Purple
static const std::string CYAN    = "\033[1;36m"; // Cyan
static const std::string WHITE   = "\033[1;37m"; // White

#endif

#endif
