BITS 16
org 0x7c00

start:
    ; Configurar la pila
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Configurar el modo protegido
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_mode

[bits 32]
protected_mode:
    ; Configurar los segmentos en modo protegido
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    ; Llamar a la funci�n kernel_main
    call kernel_main

hang:
    jmp hang

; GDT
gdt_start:
    dq 0x0000000000000000  ; Descriptor nulo
    dq 0x00CF9A000000FFFF  ; C�digo: base=0, l�mite=4G, ejecutable, de solo lectura
    dq 0x00CF92000000FFFF  ; Datos: base=0, l�mite=4G, de lectura/escritura

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55