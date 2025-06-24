; boot/boot.asm

; targeting the 32-bit protected mode.
section .multiboot
   ; required by GRUB
   dd 0x1BADB002
   dd 0x00
   dd - (0x1BADB002 + 0x00)
 
; holding the stack. reserving 16KB for it.
section .bss
stack_bottom:
   resb 16384
stack_top:


; actual startup code
section .text
global _start

_start:
   mov esp, stack_top

   extern kmain
   call kmain

   cli
.hang:
   hlt
   jmp .hang
