#ifndef HPP_SENTENCE_DEFINED
#define HPP_SENTENCE_DEFINED

// Default libraries
#include <vector>

// Libraries
#include "Token.hpp"

using Sentence = std::vector<Token>;
std::ostream &operator<<(std::ostream &os, const Sentence& sent);

#endif
