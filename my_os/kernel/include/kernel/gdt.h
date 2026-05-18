#ifndef __GDT_H
#define __GDT_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define     GDT_CODE_SEGMENT               0x08

void init_gdt();
void set_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access_rights);

extern void setGdt(gdt_descriptor*);
extern void reloadSegments();

#endif