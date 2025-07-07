#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util/vect.h"
#include "../util/dat.h"
#include "../util/token.h"

#ifndef PARSE_H
#define PARSE_H

void parse_main(Vector* src, Vector* tokv, config* cfg) {
    if (cfg->e_debug) {
        printf("Debug mode enabled.\n");
    }
    for (size_t i = 0; i < src->size; ++i) {
        char* line = (char*)vect_get(src, i);
        // ID_FN check
        if (!strncmp(line, "fn ", 3)) {
            if (cfg->e_debug) {
                printf("DEBUG: fn : %d, %s\n",i,line);
            }
            char buf[32];
            size_t k = 0;
            for (size_t j = 3; line[j] != '(' && k < sizeof(buf) - 1; ++j, ++k) {
                if (line[j] == '\0') {
                    printf("FATAL: Syntax Error Line %d (function with no parameters)\n%d: %s\n", i+1, i+1, line);
                    for (size_t o = 0; o < j; o++) {
                        printf("-");
                    }
                    printf("# (parameters where?)\n");
                    exit(1);
                }
                buf[k] = line[j];
            }

            buf[k] = '\0';
            Tok fn_token = tok_new(ID_FN, buf);
            vect_push(tokv, &fn_token);
            if (line[k] == '(') {
            }
            continue;
        }
        // ID_VAR check
        if (!strncmp(line, "int ", 4)) {

            continue;
        }
    }
}

#endif