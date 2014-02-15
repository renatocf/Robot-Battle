/**********************************************************************/
/* Copyright 2014 RCF                                                 */ 
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in compliance with the License.   */
/* You may obtain a copy of the License at                            */
/*                                                                    */
/*     http://www.apache.org/licenses/LICENSE-2.0                     */
/*                                                                    */
/* Unless required by applicable law or agreed to in writing,         */
/* software distributed under the License is distributed on an        */
/* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,       */
/* either express or implied.                                         */
/* See the License for the specific language governing permissions    */
/* and limitations under the License.                                 */
/**********************************************************************/

// Default libraries
#include <iostream>
using namespace std;

// Libraries
#include "RVM.hpp"
#include "Quark.hpp"
#include "Command.hpp"
#include "Stackable.hpp"

int main(int argc, char **argv)
{
    // Usage
    if(argc != 2)
    {
        cout << "USAGE: Main program_name.asm" << endl;
        return 0;
    }
    
    parser::quark::Func_ptr upload = parser::quark::functions[argv[1]];
    cout << upload() << endl;
    
    vm::RVM Bender { upload() };
    Bender.run();
    
    return 0;
}
