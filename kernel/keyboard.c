#include "common.h"
#include "keyboard.h"
#include "irq.h"
#include "vga.h"

// Scancode map for a US QWERTY keyboard layout.
static const unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0,
    ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

// This is the function that will be called when a key is pressed.
static void keyboard_handler(registers_t *r)
{
    u8 scancode = inb(0x60); // Read scancode from keyboard data port

    // For now, we only handle key presses, not releases.
    // The high bit of the scancode is set on key release.
    if (scancode < 128)
    {
        vga_putchar(keyboard_map[scancode]);
    }
}

// This function installs the keyboard handler into our IRQ system.
void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}
