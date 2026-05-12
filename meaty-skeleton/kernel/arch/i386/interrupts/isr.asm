[bits 32]

; create macros as there are 256 interrupts to consider
%macro ISR_NOERRORCODE 1
global isr%1
isr%1:
    push 0        ; push dummy error code
    push %1     ; push interrupt number
    jmp isr_common
%endmacro

%macro ISR_ERRORCODE 1
global isr%1
isr%1:
                ; cpu pushes an error code to the stack
    push %1     ; push interrupt number
    jmp isr_common
%endmacro

global isr_common
isr_common:
    pusha           ; pushes general-purpose registers onto the stack in the following order: 
                    ; EAX, ECX, EDX, EBX, ESP (original value), EBP, ESI, and EDI

    xor eax, eax    ; set eax to 0x00000000
    mov eax, ds     ; https://www.felixcloutier.com/x86/mov
                    ; When executing MOV Reg, Sreg, the processor copies the content of Sreg to the 16 least significant bits of the general-purpose register. 
                    ; The upper bits of the destination register are zero for most IA-32 processors (Pentium Pro processors and later) and all Intel 64 processors, 
                    ; with the exception that bits 31:16 are undefined for Intel Quark X1000 processors, Pentium, and earlier processors.

    push eax        ; push value of ds onto stack

    mov ax, 0x0010  ; move into kernel data segment as data segment is not automatically changed
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        ; pass pointer to stack to C, so we can get all the pushed info
    call isr_handler

    add esp, 4
    pop eax         ; popping ax will only pop off exactly 2-bytes and move stack pointer by 2 bytes, pop off the same size as it was pushed
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa            ; popped what was pushed with pusha
    add esp, 8      ; remove error code and interrupt number
    iret            ; will pop: cs, eip, eflags, ss, esp