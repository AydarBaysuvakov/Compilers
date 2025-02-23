#ifndef LEXER
#define LEXER

typedef enum {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    X_VAR,
    Y_VAR,
    Z_VAR,
    ENDOFLINE,
    ERROR
} token_t;

token_t getNextToken();

#endif//LEXER