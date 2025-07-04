#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

#define MAX 50

typedef enum {
    KEY,
    ID,
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX];
} Token;

#endif