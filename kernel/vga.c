#include "vga.h"
#include "common.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY (unsigned short*)0xB8000

#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5

static struct {
    unsigned short* buffer;
    u8 cursor_x;
    u8 cursor_y;
    u8 color;
} vga_state;

static void move_cursor() {
    u16 pos = vga_state.cursor_y * VGA_WIDTH + vga_state.cursor_x;

    outb(VGA_CTRL_REGISTER, 14);
    outb(VGA_DATA_REGISTER, (pos >> 8) & 0xFF);
    outb(VGA_CTRL_REGISTER, 15);
    outb(VGA_DATA_REGISTER, pos & 0xFF);
}

static void clear_screen() {
    u16 blank = 0x20 | (vga_state.color << 8);
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_state.buffer[i] = blank;
    }

    vga_state.cursor_x = 0;
    vga_state.cursor_y = 0;
    move_cursor();
}

void vga_init(void) {
    vga_state.buffer = VGA_MEMORY;
    vga_state.cursor_x = 0;
    vga_state.cursor_y = 0;
    vga_state.color = 0x0F;
    clear_screen();
}

void vga_putchar(char c) {
    if (c == '\n') {
        vga_state.cursor_x = 0;
        vga_state.cursor_y++;
    }

    move_cursor();
}

void vga_writestring(const char* data) {
    for (int i = 0; data[i] != '\n'; i++) {
        vga_putchar(data[i]);
    }
}




