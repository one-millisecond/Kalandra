#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "../util/vect.h"
#include "../util/dat.h"

void lex_main(char* arg[], config* cfg, Vector* matrix) {
    char cd[PATH_MAX];
    char path[PATH_MAX];
    if (getcwd(cd, sizeof(cd)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    snprintf(path, sizeof(path), "%s/%s", 
             (arg[cfg->in_path][0] == '/') ? "" : cd, arg[cfg->in_path]);
    if (access(path, F_OK)) {
        printf("FATAL: Failed to open file: %s\n", path);
        exit(1);
    }
    FILE *raw = fopen(path, "r");
    if (raw == NULL) {
        printf("FATAL: Failed to open file: %s\n", path);
        exit(1);
    }
    Vector *line_vec = malloc(sizeof(Vector));
    vect_init(line_vec, 10);
    char ch;
    while ((ch = fgetc(raw)) != EOF) {
        if (ch == '\n') {
            vect_push(matrix, line_vec);
            line_vec = malloc(sizeof(Vector));
            vect_init(line_vec, 10);
        } else {
            char *char_ptr = malloc(sizeof(char));
            *char_ptr = ch;
            vect_push(line_vec, char_ptr);
        }
    }
    if (line_vec->size > 0) {
        vect_push(matrix, line_vec);
    }
    fclose(raw);
}