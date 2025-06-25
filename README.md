# DooMKernel: A Hobby Microkernel OS

A minimalist, 32-bit microkernel-based operating system built from scratch with the primary goal of running the original DOOM. This is a learning project focused on understanding core OS concepts and low-level C programming.

---

## Current Status: Interactive!

The OS currently boots to a command-line-like environment and accepts keyboard input. All basic hardware interrupt handling is now in place.

### Completed Milestones (Phases)

* **Phase 1: Hello, World! Kernel:** Successfully set up a cross-compiler and build system (`make`), booted from a GRUB bootloader, and printed a message directly to the VGA text-mode buffer.
* **Phase 2: Structured VGA Driver:** Refactored primitive screen writing into a clean, reusable driver with functions like `vga_putchar()` and `vga_writestring()`. Learned to control the hardware cursor via I/O ports.
* **Phase 3: Core CPU Structures (GDT & IDT):** Initialized the Global Descriptor Table (GDT) and the Interrupt Descriptor Table (IDT), the foundational structures required for protected-mode operation and interrupt handling.
* **Phase 4: Exception Handling (ISRs):** Implemented robust assembly stubs and a C handler for the first 32 CPU exceptions (e.g., "Division by Zero," "General Protection Fault"). The OS can now safely catch its own errors.
* **Phase 5: Keyboard Input (IRQs):** Programmed the Programmable Interrupt Controller (PIC), created a generic system for handling hardware interrupts (IRQs), and wrote a keyboard driver to translate scancodes into characters on the screen.

---

## The Development Journey: Bugs Squashed & Lessons Learned

This project is as much about the process as the result. We've encountered and solved several classic OS development challenges.

* **Lesson: The Build Environment is Everything.**
    * **Bug:** `i686-elf-gcc: No such file or directory`.
    * **Solution:** The cross-compiler was built successfully but wasn't in the system's `PATH`. This taught us the importance of correctly configuring the shell environment (`~/.bashrc`) to find our specialized tools.

* **Lesson: Build Systems Must Be Explicit.**
    * **Bug:** `grub-mkrescue: No such file or directory` or `No rule to make target 'linker.ld'`.
    * **Solution:** A robust `Makefile` shouldn't just assume tools exist. We learned to install all necessary dependencies (`grub-pc-bin`, `xorriso`) and to write checks into the `Makefile` to provide clear error messages if essential files like `linker.ld` are missing.

* **Lesson: The Linker Obeys Orders, For Better or Worse.**
    * **Bug:** GRUB would complain "Multiboot header not found" even though the header was in `boot.asm`.
    * **Solution:** The order of files given to the linker is critical. We fixed the `Makefile` to *always* place the boot object files (`boot.o`) before any C object files, ensuring our multiboot header was at the very beginning of the final `kernel.bin`.

* **Lesson: The "Contract" Between C and Assembly is Tricky.**
    * **Bug:** A long series of `undefined reference to 'isr_handler'` errors.
    * **Solution:** We first suspected a missing underscore (`_`) on the C function name, a common convention. When that also failed, we realized the problem was deeper. The final, robust fix was to stop using the simple linker (`ld`) directly and instead use our cross-compiler (`i686-elf-gcc`) for the final linking step. It understands the C naming convention (the "calling convention") and automatically links necessary helper libraries like `libgcc`.

* **Lesson: Headers Define Public APIs.**
    * **Bug:** `implicit declaration of function 'idt_set_gate'`.
    * **Solution:** A function's code (`definition`) existing in one `.c` file isn't enough. For another `.c` file to use it, its `declaration` must be placed in a shared header file (`.h`). We fixed this by adding the prototype for `idt_set_gate` to `idt.h`, making it part of the IDT module's public interface.

---

## Next Steps: The Road to DOOM

With a stable, interactive foundation, our path forward is clear.

* **Phase 6: A System Timer:** We will program the Programmable Interval Timer (PIT) to fire an interrupt at a regular frequency (e.g., 100Hz). This is the heartbeat of the OS and the foundation for multitasking.
* **Phase 7: Memory Management (Paging):** This is the next major architectural step. We will implement a physical memory manager and set up paging to create virtual address spaces. This is essential for protecting memory and running multiple processes.
* **Phase 8: The Heap (Dynamic Memory):** We'll implement `kmalloc()` and `kfree()` to allow our kernel to allocate memory dynamically.
* **Phase 9: A Simple Filesystem Driver:** We will write a driver to read data from a simple, initial RAM disk (initrd), which will hold our DOOM files.
* **Phase 10: Porting DOOM:** The final goal! We will take the DOOM source code, replace its calls for input, video, and file access with calls to our own kernel's drivers, and run it.
