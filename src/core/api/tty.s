[org 0x0000]
[bits 16]

start:
    test al, al
    jz .print
    cmp al, 1
    je .newl
    stc
    iret
.print
    call print
.newl
    call newl

print:
    push ax
    push dx
    push es

    mov dx, [pos]
    shl dx, 1
    mov ax, 0xb800
    mov es, ax
.char:
    lodsb
    test al, al
    jz .done
    cmp al, 10
    je .newline
    mov word [es:dx], ax
    add dx, 2
    jmp .char
.newline:
    call newl
    mov dx, [pos]
    shl dx, 1
    jmp .char
.done:
    mov [pos], dx
    pop es
    pop dx
    pop ax
    iret

newl:
    push ax
    mov ax, [pos]
    mov bx, 80
    xor dx, dx
    div bx
    inc ax
    mul bx
    mov [pos], ax
    pop ax
    iret

pos dw 0

times 512-($-$$) db 0