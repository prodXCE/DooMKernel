#include "common.h"
#include "pic.h"

#define PIC1        0x20
#define PIC1_COMMAND PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2        0xA0
#define PIC2_COMMAND PIC2
#define PIC2_DATA   (PIC2+1)
#define PIC_EOI     0x20

void pic_remap(int offset1, int offset2) {
    u8 a1 = inb(PIC1_DATA), a2 = inb(PIC2_DATA);
    outb(PIC1_COMMAND, 0x11); outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, offset1); outb(PIC2_DATA, offset2);
    outb(PIC1_DATA, 4); outb(PIC2_DATA, 2);
    outb(PIC1_DATA, 0x01); outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, a1); outb(PIC2_DATA, a2);
}

void pic_send_eoi(u8 irq) {
    if(irq >= 8) outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}
