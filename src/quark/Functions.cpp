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

// Default Libraries
#include <vector>
#include <iostream>

// Libraries
#include "stk.hpp"
#include "Functions.hpp"
using namespace stk;

/**
 * <b>Parser for program sample/functions.asm.</b>
 * This file is automatically 
 * generated by asm2cpp.pl
 * @author asm2cpp.pl
 */
vm::Prog quark::upload_Functions()
{
    using namespace vm;
    vm::Prog PROG;

    // Numerical variables
    Int num1 { 0 };
    Int num2 { 1 };

    // Textual variables
    stk::Text msg1 { "INC" };

    PROG.push_back( vm::Command { Command::Opcode::PUSH, num1        });
    PROG.push_back( vm::Command { Command::Opcode::CALL, msg1        });
    PROG.push_back( vm::Command { Command::Opcode::CALL, msg1        });
    PROG.push_back( vm::Command { Command::Opcode::CALL, msg1        });
    PROG.push_back( vm::Command { Command::Opcode::CALL, msg1        });
    PROG.push_back( vm::Command { Command::Opcode::PRN               });
    PROG.push_back( vm::Command { Command::Opcode::END               });
    PROG.push_back( vm::Command {                              "INC" });
    PROG.push_back( vm::Command { Command::Opcode::PUSH, num2        });
    PROG.push_back( vm::Command { Command::Opcode::ADD               });
    PROG.push_back( vm::Command { Command::Opcode::RET               });

    return PROG;
}

