#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

typedef enum {
    KEY,
    ID,
} TokenType;

typedef struct {
    TokenType type;
    char value[50];
} Token;

#endif