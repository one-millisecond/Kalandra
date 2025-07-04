#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "util/dat.h"
#include "util/table.h"
#include "util/token.h"
#include "compile/out.h"
#include "compile/parse.h"

void compile_main(int argc, char* arg[], config* cfg) {
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
    TokenTable *table = parse_main(&raw);
    exit(0);
}