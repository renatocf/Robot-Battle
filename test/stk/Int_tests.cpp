// Default libraries
#include <iostream>
using namespace std;

// Internal libraries
#include "Int.hpp"
using namespace stk;

int main()
{
    // Test01: Simple integer
    Int n01 {1};
    cout << n01 << endl;
    
    // Test03: Pointer to Int
    Int *n03 = n01.create();
    cout << *n03 << endl;
    delete n03;
    
    // Test04: Cloning with pointer
    Int *n04 = n01.clone();
    cout << *n04 << endl;
    delete n04;
    
    return 0;
}
