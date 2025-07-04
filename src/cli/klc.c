#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../core/dat.h"

int main(int argc, char* arg[]) {
    printf("Kalandra Compiler v0.0.0\n");
    if (argc < 2) {
        printf("`%s -h` for help.\n", arg[0]);
    } else if (!strcmp(arg[1], "-h")) {
        printf("# Kalandra Compiler Version 0.0.0\n**See `## Notes` in `readme.md`.**\n\n"
            "## Compiler\n"
            "- `s` : Link source code path\n"
            "- `o` : Link output path\n"
        );
    }
}