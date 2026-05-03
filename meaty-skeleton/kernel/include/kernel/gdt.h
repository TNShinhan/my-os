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

// typedef enum {
//     // Accessed bit


// } ACCESS_BYTES_AND_FLAGS;

void init_gdt_segments();
void set_gdt_entry(gdt_entry* target, uint32_t base, uint32_t limit, uint8_t access_rights);

// gdt.s
extern void setGdt(gdt_descriptor*);
extern void reloadSegments();

#endif