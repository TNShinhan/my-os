#ifndef __GDT_H
#define __GDT_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t  base_hi;
    uint8_t  access_rights;
    uint8_t  flags_limit_hi;
    uint8_t  base_xhi;
} SegmentDescriptor;

typedef struct {
    SegmentDescriptor null_segment;
    SegmentDescriptor kernel_code_segment;
    SegmentDescriptor kernel_data_segment;
    // SegmentDescriptor user_code_segment;
    // SegmentDescriptor user_data_segment;
    // SegmentDescriptor task_state_segment;
} GlobalDescriptorTable;

void load_gdt_segments();
void create_gdt();
void create_segment_descriptor(SegmentDescriptor* target, uint32_t base, uint32_t limit, uint8_t access_rights);

// gdt.s
extern void setGdt(uint16_t limit, uint32_t base);
extern void reloadSegments();

#endif