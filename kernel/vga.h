#ifndef VGA_H
#define VGA_H

#include "common.h"

void vga_init(void);

void vga_putchar(char c);

void vga_writestring(const char* data);

#endif 
