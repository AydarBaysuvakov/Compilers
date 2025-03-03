#ifndef LEXER
#define LEXER

typedef enum {
    NUMBER,     //id
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    OPEN_B,
    CLOSE_B,
    X_VAR,      //id
    Y_VAR,      //id
    Z_VAR,      //id
    EXPRESSION, //E
    TERM,       //T
    PARAMETR,   //F
    ENDOFLINE,  //$
    ACCEPT,
    ERROR
} token_t;

token_t getNextToken();

#endif//LEXER