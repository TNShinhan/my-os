#ifndef __IDT_H
#define __IDT_H

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

void init_idt();
void set_idt_entry(uint8_t target, uint32_t base, uint16_t segment_descriptor, uint8_t flags);
extern void setIdt(idt_descriptor*);

#endif