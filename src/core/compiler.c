#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "compile/out.h"
#include "compile/parse.h"

#include "util/vect.h"

void compile_main(int argc, char* arg[], config* cfg) {
    lex_main(arg, &cfg);
    exit(0);
}