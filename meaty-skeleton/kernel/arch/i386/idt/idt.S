// .section .text
// .global setIdt
// .type setIdt, @function
// setIdt:
//     movl 4(%esp), %eax
//     lgdt (%eax)
//     ret

global setIdt
setIdt:
    mov  eax, [esp + 4]
    lidt [eax]
    ret