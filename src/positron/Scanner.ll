%namespace positron
%interactive

%%

[ \t]                       // ignored

[0-9]+                      return Parser::NUM;

[0-9]+("."[0-9]+)?          return Parser::NUM;

.|\n                        return matched()[0];
