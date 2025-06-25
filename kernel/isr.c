/* kernel/isr.c */

#include "isr.h"
#include "vga.h"

// Array of messages for the first 32 exceptions.
const char *exception_messages[] = {
    "Division By Zero", "Debug", "Non Maskable Interrupt", "Breakpoint",
    "Into Detected Overflow", "Out of Bounds", "Invalid Opcode", "No Coprocessor",
    "Double Fault", "Coprocessor Segment Overrun", "Bad TSS", "Segment Not Present",
    "Stack Fault", "General Protection Fault", "Page Fault", "Unknown Interrupt",
    "Coprocessor Fault", "Alignment Check", "Machine Check", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

// This is our main C interrupt handler.
void isr_handler(registers_t *regs)
{
    vga_writestring("Received Interrupt: ");

    // Check if it's a fault (an exception from 0-31)
    if (regs->int_no < 32)
    {
        vga_writestring(exception_messages[regs->int_no]);
        vga_writestring("\nSystem Halted.\n");
        // Halt the system
        for (;;);
    }
}
