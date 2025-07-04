#ifndef TABLE_H
#define TABLE_H

#include "token.h"

typedef struct {
    Token **table;
    int num_lines;
    int max_tokens_per_line;
} TokenTable;

TokenTable* create_table(int num_lines, int max_tokens_per_line) {
    TokenTable *table = malloc(sizeof(TokenTable));
    table->num_lines = num_lines;
    table->max_tokens_per_line = max_tokens_per_line;

    table->table = malloc(num_lines * sizeof(Token*));
    for (int i = 0; i < num_lines; i++) {
        table->table[i] = malloc(max_tokens_per_line * sizeof(Token));
        for (int j = 0; j < max_tokens_per_line; j++) {
            table->table[i][j].value[0] = '\0';
        }
    }

    return table;
}

void table_free(TokenTable *table) {
    for (int i = 0; i < table->num_lines; i++) {
        free(table->table[i]);
    }
    free(table->table);
    free(table);
}

void table_add(TokenTable *table, int line, int token_index, const char *token_value) {
    if (line >= table->num_lines || token_index >= table->max_tokens_per_line) {
        printf("Error: Index out of bounds (line: %d, token_index: %d)\n", line, token_index);
        return;
    }
    strncpy(table->table[line][token_index].value, token_value, 50);
}

void table_remove(TokenTable *table, int line, int token_index) {
    if (line >= table->num_lines || token_index >= table->max_tokens_per_line) {
        printf("FATAL: Index out of bounds (line: %d, index: %d)\n", line, token_index);
        exit(1);
    }
    table->table[line][token_index].value[0] = '\0';
}

void table_newl(TokenTable *table, int max_tokens_per_line) {
    table->num_lines++;
    table->table = realloc(table->table, table->num_lines * sizeof(Token*));
    table->table[table->num_lines - 1] = malloc(max_tokens_per_line * sizeof(Token));
    table->max_tokens_per_line = max_tokens_per_line;
    for (int i = 0; i < max_tokens_per_line; i++) {
        table->table[table->num_lines - 1][i].value[0] = '\0';
    }
}

#endif