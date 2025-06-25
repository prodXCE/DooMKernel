#include "common.h"
#include "irq.h"
#include "idt.h"  // FIX: Include idt.h to know about idt_set_gate
#include "pic.h"  // FIX: Include the new pic.h instead of the .c file

// --- FIX: Extern the IRQ handlers from irq.asm ---
extern void irq0(); extern void irq1(); extern void irq2(); extern void irq3();
extern void irq4(); extern void irq5(); extern void irq6(); extern void irq7();
extern void irq8(); extern void irq9(); extern void irq10(); extern void irq11();
extern void irq12(); extern void irq13(); extern void irq14(); extern void irq15();

static isr_t irq_handlers[16] = {0};

void irq_install_handler(int irq, isr_t handler) {
    irq_handlers[irq] = handler;
}

void irq_uninstall_handler(int irq) {
    irq_handlers[irq] = 0;
}

void irq_handler(registers_t *r) {
    int irq_num = r->int_no - 32;
    if (irq_handlers[irq_num] != 0) {
        isr_t handler = irq_handlers[irq_num];
        handler(r);
    }
    pic_send_eoi(irq_num);
}

void irq_install() {
    pic_remap(32, 40);

    idt_set_gate(32, (u32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (u32)irq1, 0x08, 0x8E);
    idt_set_gate(34, (u32)irq2, 0x08, 0x8E);
    idt_set_gate(35, (u32)irq3, 0x08, 0x8E);
    idt_set_gate(36, (u32)irq4, 0x08, 0x8E);
    idt_set_gate(37, (u32)irq5, 0x08, 0x8E);
    idt_set_gate(38, (u32)irq6, 0x08, 0x8E);
    idt_set_gate(39, (u32)irq7, 0x08, 0x8E);
    idt_set_gate(40, (u32)irq8, 0x08, 0x8E);
    idt_set_gate(41, (u32)irq9, 0x08, 0x8E);
    idt_set_gate(42, (u32)irq10, 0x08, 0x8E);
    idt_set_gate(43, (u32)irq11, 0x08, 0x8E);
    idt_set_gate(44, (u32)irq12, 0x08, 0x8E);
    idt_set_gate(45, (u32)irq13, 0x08, 0x8E);
    idt_set_gate(46, (u32)irq14, 0x08, 0x8E);
    idt_set_gate(47, (u32)irq15, 0x08, 0x8E);

    asm volatile("sti");
}
