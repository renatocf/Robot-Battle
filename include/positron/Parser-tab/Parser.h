// Generated by Bisonc++ V4.01.00 on Sat, 05 Apr 2014 22:58:44 -0300

#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "Parserbase.h"
// $insert scanner.h
#include "Scanner.h"

// $insert namespace-open
namespace positron
{

#undef Parser
class Parser: public ParserBase
{
    // $insert scannerobject
    Scanner d_scanner;
        
    public:
        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
};

// $insert namespace-close
}

#endif
