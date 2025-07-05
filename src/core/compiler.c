#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "compile/out.h"
#include "compile/parse.h"
#include "compile/lex.h"
#include "util/dat.h"

#include "util/vect.h"

void compile_main(int argc, char* arg[], config* cfg) {
    Vector src;
    vect_init(&src, 10);
    lex_main(arg, cfg, &src);
    exit(0);
}