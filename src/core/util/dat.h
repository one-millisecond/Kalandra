#include <stdbool.h>

#ifndef DAT_H
#define DAT_H

typedef struct {
    int out_path;
    int in_path;
    bool outtype;
    bool no_o_select;
    bool e_debug;
} config;

#endif