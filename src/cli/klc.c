#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../core/dat.h"

config cfg;

int main(int argc, char* arg[]) {
    printf("Kalandra Compiler v0.0.0\n");
    if (argc < 2) {
        printf("`%s -h` for help.\n", arg[0]);
        return 1;
    } else if (!strcmp(arg[1], "-h")) {
        printf("# Kalandra Compiler Version 0.0.0\n**See `## Notes` in `readme.md`.**\n\n"
            "## Compiler\n"
            "- `-s` : Link source code path\n"
            "- `-o` : Link output path\n\n"
        );
        return 0;
    }
    bool select_s = 0;
    bool select_o = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(arg[i], "-h")) {
            printf("WARN: -h must be at beginning, **ignoring -h**");
        }
        if (!strcmp(arg[i], "-s")) {
            if (select_s) {
                printf("WARN: Source file already selected, **ignoring duplicate -s**\n");
                continue;
            }
            if (i + 1 < argc) {
                strcpy(cfg.out_path, arg[i + 1]);
                select_s = true;
                i++;
            } else {
                printf("FATAL: Missing argument after -s\n");
                return 1;
            }
        }
    }
    
}