#ifndef IDT_H
#define IDT_H

#include "common.h"

typedef struct idt_entry_struct {
    u16 base_lo;
    u16 sel;
    u8 always0;
    u8 flags;
    u16 base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr_struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_ptr_t;

void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags);

void idt_init();

#endif
