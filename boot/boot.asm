; boot/boot.asm

bits 32

; This is the Multiboot header.
section .multiboot
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

; This section holds the stack.
section .bss
stack_bottom:
    resb 16384
stack_top:

; This section holds our actual code.
section .text
; --- Make all our functions visible to the C code ---
global _start
global gdt_flush
global idt_flush

_start:
    mov esp, stack_top
    extern kmain
    call kmain
    cli
.hang:
    hlt
    jmp .hang

; Loads the GDT pointer into the CPU's GDT register.
gdt_flush:
    mov eax, [esp+4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret

; Loads the IDT pointer into the CPU's IDT register.
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ret
