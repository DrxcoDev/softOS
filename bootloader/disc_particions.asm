section .data
    mbr db 0xEB, 0x3C, 0x90           ; Código de inicio
    partition_table db 0x80, 0x01, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00 ; Partición 1
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; Partición 2
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; Partición 3
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; Partición 4

section .text
    global _start

_start:
    ; Inicialización del MBR
    call write_mbr

    ; Fin del programa
    mov ax, 0x4C00
    int 0x21

write_mbr:
    ; Escribimos la tabla de particiones
    mov ah, 0x13        ; Función de leer/escribir discos
    mov al, 0x01        ; Número de sectores a escribir (1)
    mov ch, 0x00        ; Cilindro (0)
    mov cl, 0x02        ; Sector (2)
    mov dh, 0x00        ; Cabeza (0)
    mov bx, partition_table ; Dirección de la tabla de particiones
    int 0x13            ; Interrupción para realizar la operación
    ret

times 510 - ($ - $$) db 0 ; Rellenar hasta 510 bytes
dw 0xAA55                ; Firma del MBR

