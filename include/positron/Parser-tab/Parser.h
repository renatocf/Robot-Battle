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
// Generated by Bisonc++ V4.01.00 on Sat, 05 Apr 2014 22:58:44 -0300

#ifndef H_POSITRON_PARSER_INCLUDED
#define H_POSITRON_PARSER_INCLUDED

// Default libraries
#include <memory>

// Scanner/Parser libraries
#include "Parserbase.h"
#include "Scanner.ih"

// Libraries
#include "Syntax_S.hpp"
#include "Compiler.hpp"
#include "RVM.hpp"

#undef Parser
namespace positron 
{
    class Parser: public ParserBase
    {
        Scanner d_scanner           {};
        std::shared_ptr<ExprS> prog {};
        Compiler compiler           {};
        
        bool reading_stdin = false;
        
        public:
            explicit 
            Parser(std::istream& in  = std::cin,
                   std::ostream& out = std::cout)
                : d_scanner{in, out},
                  reading_stdin{ (in == std::cin) ? true : false } {}
            
            int parse();
            const ExprS *get_tree() const;

        private:
            void error(char const *msg); // called on (syntax) errors
            int  lex();                  // returns the next token from 
                                         // the lexical scanner. 
            void print();                // use, e.g., d_token, d_loc
        
        // support functions for parse():
            void executeAction (int ruleNr);
            void errorRecovery ();
            int  lookup        (bool recovery);
            void nextToken     ();
            void print__       ();
    };
}

#endif
