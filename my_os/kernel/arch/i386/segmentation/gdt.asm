[bits 32]
section .text
global setGdt
global reloadSegments
setGdt:
    mov eax, [esp + 4]    ; Load the pointer passed from C
    lgdt [eax]            ; Load GDT
    ret

reloadSegments:
    jmp 0x08:.reloadCS   ; Load CS segment with a jmp, can't use a mov
.reloadCS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret