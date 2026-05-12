#ifndef __GDT_H
#define __GDT_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t  base_hi;
    uint8_t  access_rights;
    uint8_t  flags_limit_hi;
    uint8_t  base_xhi;
} __attribute__((packed)) gdt_entry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_descriptor;

void init_gdt();
void set_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access_rights);

extern void setGdt(gdt_descriptor*);
extern void reloadSegments();

#endif