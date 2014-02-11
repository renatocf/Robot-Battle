// Default libraries
#include <iostream>
#include <memory>
using namespace std;

// Internal libraries
#include "Command.hpp"
#include "Number.hpp"
using namespace vm;

int main()
{
    // Test 01: Command only
    Command cmd01 { "PUSH" };
    cout << cmd01 << endl;
    
    // Test 02: Command with argument
    Command cmd02 { "PUSH", unique_ptr<stk::Stackable>{ new stk::Number{2} } };
    cout << cmd02 << endl;
    
    // Test 03: Command with argument and label
    Command cmd03 { "PUSH", unique_ptr<stk::Stackable>{ new stk::Number{2} }, "label03" };
    cout << cmd03 << endl;
    
    // Test 04: Copy constructor
    // Command cmd04 { cmd03 };
    
    return 0;
}
