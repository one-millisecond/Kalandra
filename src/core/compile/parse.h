#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util/vect.h"
#include "../util/dat.h"

#ifndef PARSE_H
#define PARSE_H

void parse_main(Vector* src, Vector* tokv) {
    for (size_t i = 0; i < src->size; ++i) {
        char* line = (char*)vect_get(src, i);
        if (!strcmp(line[0], "#")) {
            
        }
    }
}

#endif