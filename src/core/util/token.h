#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_UNKNOWN = 0,  // unknown
    TOKEN_IDENTIFIER,   // var, fn, etc
    TOKEN_KEYWORD,      // if, while, etc
    TOKEN_OPERATOR,     // +, -, etc
    TOKEN_NUMBER,       // 123, 321, etc
    TOKEN_STRING,       // "hello", 'c', etc
    TOKEN_SYMBOL,       // ;, (), etc
    TOKEN_EOF           // end of file
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

#endif