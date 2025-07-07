#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "../util/vect.h"
#include "../util/dat.h"

void lex_main(char* arg[], config* cfg, Vector* src) {
    char cd[PATH_MAX];
    char path[PATH_MAX];
    if (getcwd(cd, sizeof(cd)) == NULL) {
        perror("getcwd");
        exit(1);
    }
    snprintf(path, sizeof(path), "%s/%s", 
             (arg[cfg->in_path][0] == '/') ? "" : cd, arg[cfg->in_path]);
    if (access(path, F_OK)) {
        printf("**FATAL:** Failed to open file: %s\n", path);
        exit(1);
    }
    FILE *raw = fopen(path, "r");
    if (raw == NULL) {
        printf("**FATAL:** Failed to open file: %s\n", path);
        exit(1);
    }
    char line[PATH_MAX];
    while (fgets(line, sizeof(line), raw)) {
        line[strcspn(line, "\n")] = '\0';
        char* line_copy = malloc(strlen(line) + 1);
        strcpy(line_copy, line);
        vect_push(src, line_copy);
    }
    fclose(raw);
}