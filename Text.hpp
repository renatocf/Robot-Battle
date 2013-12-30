#ifndef HPP_TEXT_DEFINED
#define HPP_TEXT_DEFINED

// Default libraries
#include <vector>

// Libraries
#include "Sentence.hpp"

using Text = std::vector<Sentence>;
std::ostream &operator<<(std::ostream &os, const Text& text);

#endif
