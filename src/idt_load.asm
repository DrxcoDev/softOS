section .text
global idt_load

extern idt_ptr_exported

idt_load:
    ; Cargar la IDT (Interrupt Descriptor Table)
    lidt [idt_ptr_exported]
    ret