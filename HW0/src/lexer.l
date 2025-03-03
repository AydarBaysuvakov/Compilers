%{
#include "./include/tokens.h"
%}

%%

"+"             { return PLUS;      }
"-"             { return MINUS;     }
"*"             { return MULTIPLY;  }
"/"             { return DIVIDE;    }
"("             { return OPEN_B;     }
")"             { return CLOSE_B;    }
[1-9][0-9]*     { return NUMBER;    }
[0-9]           { return NUMBER;    }
"x"             { return X_VAR;     }
"y"             { return Y_VAR;     }
"z"             { return Z_VAR;     }
"\n"            { return ENDOFLINE; }
"$"             { return ENDOFLINE; }
[ \t\r]+        { /* ignore */      }
.               { return ERROR;     }

%%

int yywrap(){}

token_t getNextToken() {
    return yylex();
}