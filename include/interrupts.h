#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdint.h>

typedef void (*interrupt_handler_t)(void);

// Configura la IDT y registra los manejadores de interrupciones.
void init_idt();

// Registra un manejador de interrupciones para una IRQ espec�fica.
void register_interrupt_handler(uint8_t irq, interrupt_handler_t handler);

// Declaraci�n de la funci�n idt_load definida en ensamblador
extern void idt_load();

#endif // INTERRUPTS_H