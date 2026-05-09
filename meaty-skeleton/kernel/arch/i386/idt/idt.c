#include <kernel/idt.h>
#include <kernel/pic.h>
#include <string.h>

#define     GDT_CODE_SEGMENT               0x08

// Gate types
#define     GATE_FLAG_16_BIT_TASK          0x05
#define     GATE_FLAG_16_BIT_INTERRUPT     0x06
#define     GATE_FLAG_16_BIT_TRAP          0x07
#define     GATE_FLAG_32_BIT_INTERRUPT     0x0E
#define     GATE_FLAG_32_BIT_TRAP          0x0F

// 0-bit between Gate Type and DPL

// DPL (CPU Privilege Levels)
#define     GATE_FLAG_RING0                (0 << 5)
#define     GATE_FLAG_RING1                (1 << 5)
#define     GATE_FLAG_RING2                (2 << 5)
#define     GATE_FLAG_RING3                (3 << 5)

// Presnet Bit
#define     GATE_FLAG_PRESENT              (1 << 7)

// Standard Interrupt Flags
#define     INT_GATE_32_BIT_PL0            GATE_FLAG_PRESENT | GATE_FLAG_32_BIT_INTERRUPT | GATE_FLAG_RING0



// Define as static/global since the IDT on the stack may be overwritten
idt_entry idt[256];
idt_descriptor idt_ptr = {sizeof(idt) - 1, (uint32_t)idt};

void init_idt() {
    memset(&idt, 0, sizeof(idt));

    init_pic();

    // Reserved exceptions
    set_idt_entry(0, (uint32_t)isr0, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(1, (uint32_t)isr1, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(2, (uint32_t)isr2, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(3, (uint32_t)isr3, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(4, (uint32_t)isr4, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(5, (uint32_t)isr5, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(6, (uint32_t)isr6, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(7, (uint32_t)isr7, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(8, (uint32_t)isr8, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(9, (uint32_t)isr9, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(10, (uint32_t)isr10, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(11, (uint32_t)isr11, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(12, (uint32_t)isr12, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(13, (uint32_t)isr13, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(14, (uint32_t)isr14, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(15, (uint32_t)isr15, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(16, (uint32_t)isr16, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(17, (uint32_t)isr17, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(18, (uint32_t)isr18, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(19, (uint32_t)isr19, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(20, (uint32_t)isr20, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(21, (uint32_t)isr21, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(22, (uint32_t)isr22, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(23, (uint32_t)isr23, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(24, (uint32_t)isr24, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(25, (uint32_t)isr25, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(26, (uint32_t)isr26, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(27, (uint32_t)isr27, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(28, (uint32_t)isr28, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(29, (uint32_t)isr29, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(30, (uint32_t)isr30, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(31, (uint32_t)isr31, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);

    // External Interrupts
    set_idt_entry(32, (uint32_t)irq0, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(33, (uint32_t)irq1, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(34, (uint32_t)irq2, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(35, (uint32_t)irq3, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(36, (uint32_t)irq4, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(37, (uint32_t)irq5, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(38, (uint32_t)irq6, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(39, (uint32_t)irq7, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(40, (uint32_t)irq8, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(41, (uint32_t)irq9, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(42, (uint32_t)irq10, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(43, (uint32_t)irq11, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(44, (uint32_t)irq12, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(45, (uint32_t)irq13, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(46, (uint32_t)irq14, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);
    set_idt_entry(47, (uint32_t)irq15, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0);

    set_idt_entry(128, (uint32_t)isr128, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0); //System calls
    set_idt_entry(177, (uint32_t)isr177, GDT_CODE_SEGMENT, INT_GATE_32_BIT_PL0); //System calls

    setIdt(&idt_ptr);
}

void set_idt_entry(uint8_t target, uint32_t base, uint16_t segment_descriptor, uint8_t flags) {
    idt[target].base_lo             =  base & 0x0000FFFF;
    idt[target].base_hi             = (base & 0xFFFF0000) >> 16;
    idt[target].segment_selector    = segment_descriptor;
    idt[target].reserved            = 0;
    idt[target].flags               = flags;
}