#include <kernel/idt.h>
#include <kernel/isr.h>

static const char* const exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(interrupt_registers* registers) {
    if(registers->interrupt >= 32)
        printf("Unhandled interrupt number %d!\n", registers->interrupt);
    else {
        printf(exception_messages[registers->interrupt]);
        printf("\n");
        printf("Interrupt=%s  Errorcode=%d\n", exception_messages[registers->interrupt], registers->error);
        printf("Exception! System Halted!\n");
        for(;;);
    }
}