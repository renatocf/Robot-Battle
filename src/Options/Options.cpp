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
        { 0, 0, 0, 0 }
    };
    
    int option_index = 0; int c;
    while((c = getopt_long(argc, argv, "d",
               long_options, &option_index)) != -1)
    {
        switch(c) 
        {
            case 'd':
                std::cout << "option d" << std::endl;
                vm::Debug::OFF = false;
                break;
            case '?':
                break;
            default:
                std::cout << "?? getopt returned character code 0" << c << " ??" << std::endl;
        }
    }
}
