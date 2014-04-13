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

%token IF
%token ELSE
%token INT
%token FLOAT
%token EOL
%stype positron::ExprS*

// ↓ Precedence increases
%left  '+' '-'
%left  '*' '/' '%'
%right NEG     // Unary minus

%%
input:
    EOF
|
    comseq EOF
    {
        prog = std::shared_ptr<ExprS>{$1};
        if(reading_stdin) ACCEPT();
    }
;

comseq:
    command comseq
    {
        $$ = new seqS{ $1, $2 };
    }
|
    command
;

command:
    conditional
|
    expr ';'
;

block:
    '{' comseq '}'
|
    command
;

conditional:
    IF '(' arith ')' block ELSE block
    {
        $$ = new ifS{ $3, $5, $7 };
    }
|
    IF '(' arith ')' block
    {
        $$ = new ifS{ $3, $5 };
    }
;

expr:
    arith
    {
        $$ = new printS{$1};
    }
;

arith:
    INT   { $$ = new intS{std::atoi(d_scanner.matched().c_str())}; }
|
    FLOAT 
    { 
        $$ = new floatS{
             static_cast<float>(std::atof(d_scanner.matched().c_str()))}; 
    }
| 
    arith '+' arith 
    { 
        $$ = new plusS{$1,$3};    
    }
| 
    arith '-' arith
    { 
        $$ = new bminusS{$1,$3};
    }
| 
    arith '*' arith
    { 
        $$ = new multS{$1,$3};    
    }
| 
    arith '/' arith
    { 
        $$ = new divS{$1,$3};    
    }
| 
    arith '%' arith
    { 
        $$ = new modS{$1,$3};    
    }
|
    // Unary minus:
    '-' arith %prec NEG
    {
        $$ = new uminusS{$2};
    }
|
    '(' arith ')'
    { 
        $$ = $2;
    }
;
