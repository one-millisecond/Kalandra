extern void print(const char* str, unsigned char color);

void _start(void) {
    print("Hello", 0xFF);
    for (;;) {}
}
