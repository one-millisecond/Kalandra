[org 0x0000]
[bits 16]

start:
    mov ah, 02h
    mov al, 1
    xor cx, cx
    mov cl, 3
    xor dx, dx
    mov dl, 0x80

    mov bx, 0x1000
    mov es, bx
    mov ds, bx
    mov ss, bx
    mov bx, 0x0000
    mov sp, bx

    int 13h
    jc err


msg_yes db ' [OK!]',0
msg_0 db 'BootManager',0

times 512 - ($ - $$) db 0