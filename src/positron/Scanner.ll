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
%interactive
%x string

%%

[ \t]                       // ignored

[0-9]+                      return Parser::INT;
[0-9]+"."[0-9]+             return Parser::FLOAT;

"\""[^"]*"\""               return Parser::STRING;

\"                          { 
                                more();
                                begin(StartCondition__::string); 
                            }

<string>\"                  {
                                begin(StartCondition__::INITIAL);
                                return Parser::STRING;
                            }

<string>\\.|.               more();

"=="|"eq"                   return Parser::EQ;
"!="|"ne"                   return Parser::NE;
"<"|"lt"                    return Parser::LT;
">"|"gt"                    return Parser::LE;
"<="|"le"                   return Parser::GT;
">="|"ge"                   return Parser::GE;

if                          return Parser::IF;
else                        return Parser::ELSE;

print                       return Parser::PRINT;

"\\\n"                      { 
                                if(reading_stdin) std::cout << "- ";
                                else return matched()[0];
                            }

\n                          if(reading_stdin) return EOF;

.                           return matched()[0];

