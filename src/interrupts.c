#include "../include/interrupts.h"
#include "../include/io.h"


// Definir la estructura IDT
struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256
struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idtp;

interrupt_handler_t interrupt_handlers[IDT_ENTRIES] = {0};

extern void idt_load();  // Declaraci�n de la funci�n idt_load

// Exportar idtp para ensamblador
__attribute__((used)) struct idt_ptr idt_ptr_exported = {0};

// Configura una entrada en la IDT
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// Inicializa la IDT y carga los handlers
void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    // Inicializar la IDT
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0x08, 0x8E);
    }

    // Actualizar la estructura exportada
    idt_ptr_exported.limit = idtp.limit;
    idt_ptr_exported.base = idtp.base;

    // Cargar la IDT
    idt_load();
}

// Registra un manejador de interrupciones para una IRQ espec�fica
void register_interrupt_handler(uint8_t irq, interrupt_handler_t handler) {
    interrupt_handlers[irq] = handler;
}

// Handler gen�rico de interrupciones
void interrupt_handler(uint8_t irq) {
    if (interrupt_handlers[irq]) {
        interrupt_handlers[irq]();
    }

    // Enviar EOI (End of Interrupt) al PIC
    if (irq >= 40) {
        outb(0xA0, 0x20); // Enviar EOI al PIC secundario
    }
    outb(0x20, 0x20); // Enviar EOI al PIC primario
}