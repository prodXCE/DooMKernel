#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "keyboard.h"

void kmain(void)
{
    gdt_init();
    idt_init();         // Installs our new, robust ISRs
    irq_install();      // Installs the hardware IRQ handlers
    keyboard_install(); // Hooks the keyboard handler to IRQ1

    vga_init();
    vga_writestring("DooMKernel Phase 5 (Revised) Complete!\n");
    vga_writestring("Robust exception handlers and keyboard are active.\n\n");

    // Let's test our new exception handler by causing a divide-by-zero error.
    // The OS should catch this, print a message, and halt.
    // Comment this line out to use the keyboard.
    // int x = 5 / 0;

    // The OS now waits for interrupts in an infinite loop.
    for(;;);
}
