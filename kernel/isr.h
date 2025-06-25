/* kernel/isr.h */

#ifndef ISR_H
#define ISR_H

#include "common.h"

typedef struct registers {
    u32 ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_code;
    u32 eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t*);

void isr_handler(registers_t* regs);

#endif
