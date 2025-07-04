#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../core/util/dat.h"

config cfg;

int main(int argc, char* arg[]) {
    if (argc < 2) {
        printf("`%s -h` for help.\n", arg[0]);
        return 1;
    } else if (!strcmp(arg[1], "-h")) {
        printf("# Kalandra Language Compiler\n**See `## Notes` in `readme.md`.**\n\n"
            "## Compiling\n"
            "- `-s` : Link source code path\n"
            "- `-o` : Link output path\n"
            "- `-a` : Output only Intel 8086/8088 assembly\n\n"
            "## Kalandra CLI\n\n"
            "- `-v` : Show Kalandra Langauge Compiler (KLC) version details\n\n"
        );
        return 0;
    } else if (!strcmp(arg[1], "-v")) {
        printf("# Kalandra Language Compiler\n**See `## Notes` in `readme.md`.**\n\n"
            "## Version\n"
            "- Syntax Version: KPL21\n"
            "- Compiler Version: 0.0.0 (Linux-x86_64)\n\n"
            "## Compiler Architectures\n\n"
            "-m 86 : Compile to Intel 8086/8088\n\n"
        );
        return 0;
    }
    bool select_s = 0;
    bool select_o = 0;
    bool select_a = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(arg[i], "-h")) {
            printf("WARN: `-h` must be at beginning, **ignoring -h**\n");
            continue;
        } else if (!strcmp(arg[i], "-v")) {
            printf("WARN: `-v` must be at beginning, **ingoring -v**\n");
            continue;
        }
        if (!strcmp(arg[i], "-s")) {
            if (select_s) {
                printf("WARN: Source file already selected, **ignoring duplicate -s**\n");
                i++;
                continue;
            }
            if (i + 1 < argc) {
                cfg.in_path = i+1;
                select_s = true;
                i++;
            } else {
                printf("FATAL: Missing argument after -s\n");
                return 1;
            }
            continue;
        }
        if (!strcmp(arg[i], "-o")) {
            if (select_o) {
                printf("WARN: Output path already selected, **ignoring duplicate -o**\n");
                i++;
                continue;
            }
            if (i + 1 < argc) {
                cfg.out_path = i+1;
                select_s = true;
                i++;
            } else {
                printf("FATAL: Missing argument after -o\n");
                return 1;
            }
            continue;
        }
        if (!strcmp(arg[i], "-a")) {
            if (select_o) {
                printf("WARN: Assembly output already selected, **ignoring duplicate -a**\n");
                continue;
            }
            cfg.outtype = 1;
            continue;
        }
        printf("FATAL: Invalid argument (%d, '%s')\n", i, arg[i]);
        return 1;
    }
    if (!select_s) {
        printf("FATAL: Source never given\n");
        return 1;
    } else if (!select_o) {
        cfg.out_path = cfg.in_path;
        cfg.no_o_select = 1;
    }
    compile_main(argc, arg, &cfg);
}