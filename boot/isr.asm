; boot/isr.asm

; Expose the handler written in C
extern isr_handler

; --- Macros ---

; ISR without error code
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    cli
    push dword 0      ; Push fake error code
    push dword %1     ; Push interrupt number
    jmp isr_common_stub
%endmacro

; ISR with error code (CPU pushes the error code)
%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    cli
    push dword %1     ; Push interrupt number
    jmp isr_common_stub
%endmacro

; --- Define all 32 ISRs (0–31) ---
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE  10
ISR_ERRCODE  11
ISR_ERRCODE  12
ISR_ERRCODE  13
ISR_ERRCODE  14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

; --- Common ISR stub handler ---
global isr_common_stub
isr_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10  ; Load kernel data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8    ; Pop error code and int_no
    iret
