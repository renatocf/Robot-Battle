/**********************************************************************/
/* Copyright 2014 RCF                                                 */ 
/*                                                                    */
/* Licensed under the Apache License, Version 2.0 (the "License");    */
/* you may not use this file except in cmdpliance with the License.   */
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
#include <string>
#include <iomanip>
#include <iostream>

// Libraries
#include "Colors.hpp"
#include "Number.hpp"
#include "Command.hpp"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                Command                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream& vm::operator<<(std::ostream& os, const Command& cmd)
{
    os << "[";
    (cmd.cmd != vm::Command::Command::Opcode::NONE) 
        ? os << vm::to_string(cmd.cmd) 
        : os << "none";
    os << ",";
    (cmd.arg)       ? os << cmd.arg->to_string() : os << "none";
    os << ",";
    (cmd.lab != "") ? os << cmd.lab : os << "none";
    os << "]";
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 Opcode                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::string vm::to_string(const vm::Command::Opcode& op)
{
    switch(op)
    {
        case Command::Opcode::NONE: return "NONE";
        case Command::Opcode::PRN:  return "PRN";
        case Command::Opcode::PUSH: return "PUSH";
        case Command::Opcode::POP:  return "POP";
        case Command::Opcode::SWAP: return "SWAP"; 
        case Command::Opcode::DUP:  return "DUP";
        case Command::Opcode::ADD:  return "ADD";
        case Command::Opcode::SUB:  return "SUB";
        case Command::Opcode::DIV:  return "DIV";
        case Command::Opcode::MUL:  return "MUL";
        case Command::Opcode::MOD:  return "MOD";
        case Command::Opcode::STO:  return "STO";
        case Command::Opcode::RCL:  return "RCL";
        case Command::Opcode::EQ:   return "EQ";
        case Command::Opcode::NE:   return "NE";
        case Command::Opcode::NIL:  return "NIL";
        case Command::Opcode::GT:   return "GT";
        case Command::Opcode::GE:   return "GE";
        case Command::Opcode::LT:   return "LT";
        case Command::Opcode::LE:   return "LE";
        case Command::Opcode::JMP:  return "JMP";
        case Command::Opcode::JIT:  return "JIT";
        case Command::Opcode::JIF:  return "JIF";
        case Command::Opcode::NOP:  return "NOP";
        case Command::Opcode::END:  return "END";
        case Command::Opcode::CALL: return "CALL";
        case Command::Opcode::RET:  return "RET";
        case Command::Opcode::DRAG: return "DRAG";
        case Command::Opcode::DROP: return "DROP";
        case Command::Opcode::HIT:  return "HIT";
        case Command::Opcode::LOOK: return "LOOK";
        case Command::Opcode::SEE:  return "SEE";
        case Command::Opcode::ASK:  return "ASK";
        case Command::Opcode::ITEM: return "ITEM";
        case Command::Opcode::SEEK: return "SEEK";
        case Command::Opcode::ALOC: return "ALOC";
        case Command::Opcode::FREE: return "FREE";
        case Command::Opcode::GET:  return "GET";
        case Command::Opcode::SET:  return "SET";
        case Command::Opcode::READ: return "READ";
        case Command::Opcode::WRT:  return "WRT";
        case Command::Opcode::SEND: return "SEND";
        case Command::Opcode::COOR: return "COOR";
        case Command::Opcode::GTIJ: return "GTIJ";
    }
    return "";
}

std::ostream& vm::operator<<(std::ostream& os, const Command::Opcode& op)
{
    os << vm::to_string(op);
    return os;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  PROG                                  
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
std::ostream& vm::operator<<(std::ostream& os, const Prog& prog)
{
    unsigned int max_cmd = 0, max_arg = 0, max_lab = 0;
    for(const Command& cmd : prog)
    {
        if(vm::to_string(cmd.cmd).size() > max_cmd) 
            max_cmd = vm::to_string(cmd.cmd).size();
        if(cmd.arg && cmd.arg->to_string().size() > max_arg) 
            max_arg = cmd.arg->to_string().size();
        if(cmd.lab.size() > max_lab) max_lab = cmd.lab.size();
    }
    if(max_lab != 0) max_lab += 2;
    
    bool first = true;
    for(const Command& cmd : prog)
    {
        // Jump line
        (first) ? first = false : os << std::endl;
        
        // Label
        (cmd.lab != "")
            ? os << BLUE    << std::setw(max_lab) << (cmd.lab + ": ") 
            : os << RESTORE << std::setw(max_lab) << "";
        
        // Command
        os << YELLOW << std::left << std::setw(max_cmd) << cmd.cmd << RESTORE;
        
        // Argument
        os << "  ";
        os << PURPLE << std::left << std::setw(max_arg) 
           << ((cmd.arg) ? cmd.arg->to_string() : "") 
           << RESTORE;
    }
    
    return os;
}
