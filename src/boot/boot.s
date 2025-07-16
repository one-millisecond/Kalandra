[org 0x7c00]
[bits 16]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov ah, 02h
    mov al, 1
    xor cx, cx
    mov cl, 2
    xor dx, dx
    mov dl, 0x80

    mov bx, 0x2000
    mov es, bx
    mov ds, bx
    mov ss, bx
    mov bx, 0x0200
    mov sp, bx

    int 13h
    jc err

    mov ah, 0x00
    mov al, 0x03
    int 0x10
    jmp 0x2000:0x0200

err:
    jmp $

times 510 - ($-$$) db 0
dw 0xAA55