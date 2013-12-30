// Default libraries
#include <string>
#include <unordered_map>

// Libraries
#include "Grammar.hpp"

std::unordered_map<char,std::string> assembly_symbol_table
{
    { '+', "ADD" },
    { '-', "SUB" },
    { '*', "MUL" },
    { '/', "DIV" },
    { '%', "MOD" },
};
