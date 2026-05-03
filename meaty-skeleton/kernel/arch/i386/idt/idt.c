#include <kernel/idt.h>
#include <libc/include/string.h>

void init_idt() {
    memset(&idt, 0, sizeof(idt));
}

void set_idt_entry(uint8_t target, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[target].base_lo             =  base & 0x0000FFFF;
    idt[target].base_hi             = (base & 0xFFFF0000) >> 16;
    idt[target].segment_selector    = sel;
    idt[target].reserved            = 0;
    idt[target].flags               = flags;
}