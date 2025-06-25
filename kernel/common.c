/*  kernel/common.h  */
#include "common.h"

// write a byte out to the specified port
void outb(u16 port, u8 value) {
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8 inb(u16 port) {
    u8 ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}
