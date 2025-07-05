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
    vect_init(&src, 1);
    Vector tokv;
    vect_init(&tokv, 10);
    lex_main(arg, cfg, &src);
    parse_main(&src, &tokv);
    vect_free(&tokv);
    vect_free(&src);
    exit(0);
}