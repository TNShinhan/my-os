[bits 32]

global setIdt
setIdt:
    mov  eax, [esp + 4]
    lidt [eax]
    sli
    ret

