//********************************************************************//
// Copyright 2014 RCF                                                 // 
//                                                                    //
// Licensed under the Apache License, Version 2.0 (the "License");    //
// you may not use this file except in compliance with the License.   //
// You may obtain a copy of the License at                            //
//                                                                    //
//     http://www.apache.org/licenses/LICENSE-2.0                     //
//                                                                    //
// Unless required by applicable law or agreed to in writing,         //
// software distributed under the License is distributed on an        //
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,       //
// either express or implied.                                         //
// See the License for the specific language governing permissions    //
// and limitations under the License.                                 //
//********************************************************************//

%namespace positron
%scanner   Scanner.h

%baseclass-preinclude Syntax_S.hpp 

%token NUM
%stype positron::ExprS*

// ↓ Precedence increases
%left  '+' '-'
%left  '*' '/'
%left  NEG     // Unary minus

%%
input:    
    // empty 
| 
    input line
;

line:   
    '\n'
| 
    exp '\n'
    {
        prog = std::shared_ptr<ExprS>{$1};
        vm::Prog assembly { Compiler{}.compile(prog.get()) }; 
        std::cout << assembly << std::endl;
        vm::RVM{ assembly }.run();
    }
;

exp:      
    NUM { $$ = new numS{std::atoi(d_scanner.matched().c_str())}; }
| 
    exp '+' exp 
    { 
        $$ = new plusS{$1,$3};    
    }
| 
    exp '-' exp
    { 
        $$ = new bminusS{$1,$3};
    }
| 
    exp '*' exp
    { 
        $$ = new multS{$1,$3};    
    }
| 
    exp '/' exp
    { 
        $$ = new divS{$1,$3};    
    }
|
    // Unary minus:
    '-' exp %prec NEG
    {
        $$ = new uminusS{$2};
    }
|
    '(' exp ')'
    { 
        $$ = $2;
    }
;
