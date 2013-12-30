#ifndef HPP_COMMAND_DEFINED
#define HPP_COMMAND_DEFINED

// Default libraries
#include <string>

class Command
{
    public:
        const std::string com; // command
        const std::string arg; // argument
        const std::string lab; // label
        
        Command()
            : com{""}, arg{""}, lab{""} {}
        Command(std::string com)
            : com{com}, arg{""}, lab{""} {}
        Command(std::string com, std::string arg)
            : com{com}, arg{arg}, lab{""} {}
        Command(std::string com, std::string arg, std::string lab)
            : com{com}, arg{arg}, lab{lab} {}
        
        friend std::ostream &operator<<(std::ostream &os, const Command& com);
};

#endif
