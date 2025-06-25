/* kernel/irq.h */

#ifndef IRQ_H
#define IRQ_H

#include "isr.h"

void irq_install();
void irq_install_handler(int irq, isr_t handler);
void irq_uninstall_handler(int irq);

#endif
