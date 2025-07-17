#include "../api/ttyservice.h"

int _start() {
    print_literal(0x0F); // white on black
    for (;;) ;           // halt
    return 0;
}
