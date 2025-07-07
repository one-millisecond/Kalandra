#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    T_UNKNOWN,
    EOL,
    KEYW,
    TYPE,
    ID_FN,
    ID_INT,
    ID_CHAR,
    ID_PTR_C,
    ID_PTR_I
} TType;

typedef struct {
    TType type;
    char* value;
} Tok;

Tok tok_new(TType type, char* value) {
    Tok token;
    token.type = type;
    token.value = value;
    return token;
}

#endif