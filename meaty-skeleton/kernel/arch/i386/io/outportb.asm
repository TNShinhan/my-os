[bits 32]

global outPortB
outPortB:
    mov dx, [esp + 4]   ; Move port number into dx (I/O pointer) (16-bit register)
    mov al, [esp + 8]   ; Move value into ax (16-bit register)
    out dx, al          ; Copies the value from the second operand (source operand) to the I/O port specified with the destination operand (first operand)
    ret