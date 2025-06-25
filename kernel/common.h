/*  kernel/common.h  */

#ifndef COMMON_H
#define COMMON_H


typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

// Function to write a byte to an I/O port
void outb(u16 port, u8 value);

// Function to read a byte from an I/O port
u8 inb(u16 port);

#endif // COMMON_H

