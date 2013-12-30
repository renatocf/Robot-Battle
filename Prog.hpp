#ifndef HPP_PROG_DEFINED
#define HPP_PROG_DEFINED

// Default libraries
#include <vector>

// Libraries
#include "Command.hpp"

using Prog = std::vector<Command>;
std::ostream &operator<<(std::ostream &os, const Prog& prog);

#endif
