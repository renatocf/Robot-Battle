// Default libraries
#include <iostream>
using namespace std;

// Internal libraries
#include "RVM.hpp"

void vm::RVM::exec() const
{
    if(this->PROG[this->PC].cmd != "")
    {
        cout << this->PROG[this->PC] << endl;
    }
}

void vm::RVM::run()  const
{
    switch(this->activity)
    {
        case State::ACTIVE:
            for(unsigned int i = 0; i < this->PROG.size(); i++)
            { 
                this->exec(); 
                if(!this->syscall) ++this->PC;
            }
            this->PC = 0;
            break;
            
        case State::SLEEP:
            if(this->PC != 0)
                { --this->PC; this->exec(); ++this->PC; }
            
            break;
    }
}
