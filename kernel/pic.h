/* kernel/pic.h */

#ifndef PIC_H
#define PIC_H

#include "common.h"

void pic_remap(int offset1, int offset2);
void pic_send_eoi(u8 irq);

#endif // PIC_H
