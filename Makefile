# Makefile

# --- Configuration ---
CC = i686-elf-gcc
AS = nasm
LD = i686-elf-ld
CFLAGS = -g -ffreestanding -Wall -Wextra -I./

# --- File Definitions ---
LINKER_SCRIPT = linker.ld

# Check for essential files before we start. This gives better errors.
ifeq ($(wildcard $(LINKER_SCRIPT)),)
    $(error Cannot find linker script '$(LINKER_SCRIPT)'. Please ensure it exists in the root project directory.)
endif

# Find all .c and .asm files in our source directories (simplified paths)
C_SOURCES = $(wildcard kernel/*.c)
ASM_SOURCES = $(wildcard boot/*.asm)

# Check that we actually found source files.
ifeq ($(C_SOURCES),)
    $(error No C source files found in kernel/. Please check your project structure.)
endif
ifeq ($(ASM_SOURCES),)
    $(error No Assembly source files found in boot/. Please check your project structure.)
endif

# Convert source file names to object file names
OBJ_FILES_C = $(patsubst %.c, build/obj/%.o, $(C_SOURCES))
OBJ_FILES_ASM = $(patsubst %.asm, build/obj/%.o, $(ASM_SOURCES))

# Final output file names
KERNEL_BIN = build/kernel.bin
ISO_FILE = build/doomkernel.iso

# --- Build Rules ---

all: $(ISO_FILE)

run: $(ISO_FILE)
	qemu-system-i386 -cdrom $(ISO_FILE)

$(ISO_FILE): $(KERNEL_BIN) boot/grub.cfg
	mkdir -p build/iso/boot/grub
	cp $(KERNEL_BIN) build/iso/boot/kernel.bin
	cp boot/grub.cfg build/iso/boot/grub/grub.cfg
	grub2-mkrescue -o $(ISO_FILE) build/iso

# Link the kernel. The order of object files matters!
# We put the assembly object files first to ensure _start is at the beginning.
$(KERNEL_BIN): $(OBJ_FILES_ASM) $(OBJ_FILES_C) $(LINKER_SCRIPT)
	$(LD) -T $(LINKER_SCRIPT) -o $(KERNEL_BIN) $(OBJ_FILES_ASM) $(OBJ_FILES_C)

# Compile C files
build/obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble assembly files
build/obj/%.o: %.asm
	mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

clean:
	rm -rf build/

.PHONY: all run clean
