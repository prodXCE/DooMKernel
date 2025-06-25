//
// Created by akashrya on 6/24/25.
//

#ifndef GDT_H
#define GDT_H

#include "common.h"

typedef struct gdt_entry_struct {
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_init();


#endif //GDT_H
