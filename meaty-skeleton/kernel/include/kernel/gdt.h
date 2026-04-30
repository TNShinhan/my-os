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
} __attribute__((packed)) segment_descriptor_struct;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_struct;

void init_gdt_segments();
void create_segment_descriptor(segment_descriptor_struct* target, uint32_t base, uint32_t limit, uint8_t access_rights);

// gdt.s
extern void setGdt(gdt_ptr_struct*);
extern void reloadSegments();

#endif