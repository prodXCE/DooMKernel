#include "gdt.h"

gdt_entry_t gdt_entries[3];
gdt_ptr_t gdt_ptr;

// external assembly function to load the GDT register
extern void gdt_flush(u32);

// Function to setup a GDT entry
static void gdt_set_gate(s32 num, u32 base, u32 limit, u8 access, u8 gran) {
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base > 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;
}

void gdt_init() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base = (u32)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    gdt_flush((u32)&gdt_ptr);

}
