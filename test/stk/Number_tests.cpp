// Default libraries
#include <iostream>
using namespace std;

// Internal libraries
#include "Number.hpp"
using namespace stk;

int main()
{
    // Test01: Simple integer
    Number n01 {1};
    cout << n01 << endl;
    
    // Test02: Simple floating point
    Number n02 {1.5};
    cout << n02 << endl;
    
    // Test03: Pointer to Number
    Number *n03 = n01.create();
    cout << *n03 << endl;
    delete n03;
    
    // Test04: Cloning with pointer
    Number *n04 = n01.clone();
    cout << *n04 << endl;
    delete n04;
    
    return 0;
}
