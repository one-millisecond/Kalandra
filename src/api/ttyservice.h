#define MKFP(seg, off) ((void __far *)(((unsigned long)(seg) << 16) | ((unsigned short)(off))))

#ifndef TTYSERVICE_H
#define TTYSERVICE_H

void print(const char __far* s, unsigned int color) {
    char __far *text = (char __far *)MKFP(0xB800, 0x0000);
    int i = 0;
    int j = 0;
    for (i; s[j] != '\n';) {
        text[i] == s[j] | color << 8;
    }
}

#endif