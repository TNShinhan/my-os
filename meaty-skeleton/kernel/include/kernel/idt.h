#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t base_lo;
    uint16_t segment_selector;
    uint8_t  reserved;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_descriptor;

typedef enum {
    // Gate Types
    GATE_FLAG_16_BIT_TASK          = 0x5,
    GATE_FLAG_16_BIT_INTERRUPT     = 0x6,
    GATE_FLAG_16_BIT_TRAP          = 0x7,
    GATE_FLAG_32_BIT_INTERRUPT     = 0xE,
    GATE_FLAG_32_BIT_TRAP          = 0xF,

    // 0-bit between Gate Type and DPL

    // DPL (CPU Privilege Levels)
    GATE_FLAG_RING0                = (0 << 5),
    GATE_FLAG_RING1                = (1 << 5),
    GATE_FLAG_RING2                = (2 << 5),
    GATE_FLAG_RING3                = (3 << 5),

    // Presnet Bit
    GATE_FLAG_PRESENT              = (1 << 7),
} GATE_FLAGS;

// Define as static/global since the IDT on the stack may be overwritten
idt_entry idt[256];
idt_descriptor idt_ptr = {sizeof(idt) - 1, (uint32_t)idt};

void init_idt();
void set_idt_entry(uint8_t target, uint32_t base, uint16_t sel, uint8_t flags);

#endif