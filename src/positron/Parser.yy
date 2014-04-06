%namespace positron
%scanner   Scanner.h

%baseclass-preinclude cmath

%token NUM
%stype double

%left  '+' '-'
%left  '*' '/'
%left  NEG     // Unary minus
%right '^'     // Exponentiation

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
        std::cout << "\t" << $1 << std::endl;
    }
;

exp:      
    NUM { $$ = std::atof(d_scanner.matched().c_str()); }
| 
    exp '+' exp 
    { 
        $$ = $1 + $3;    
    }
| 
    exp '-' exp
    { 
        $$ = $1 - $3;    
    }
| 
    exp '*' exp
    { 
        $$ = $1 * $3;    
    }
| 
    exp '/' exp
    { 
        $$ = $1 / $3;    
    }
|
    // Unary minus:
    '-' exp %prec NEG
    {
        $$ = -$2;
    }
|
    // Exponentiation:
    exp '^' exp
    { 
        $$ = pow($1, $3);
    }
|
    // Exponentiation:
    '(' exp ')'
    { 
        $$ = $2;
    }
;
