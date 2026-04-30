#include <kernel/gdt.h>

// Define as static/global since the GDT on the stack may be overwritten
static segment_descriptor_struct gdt[5];
static gdt_ptr_struct gdt_ptr;

void init_gdt_segments() {
    printf("Creating gdt...\n");

    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base  = (uint32_t)&gdt;

    create_segment_descriptor(&gdt[0], 0, 0, 0);                    // Unused segment
    create_segment_descriptor(&gdt[1], 0, 64 * 1024 * 1024, 0x9A);  // Kernel Code Segment
    create_segment_descriptor(&gdt[2], 0, 64 * 1024 * 1024, 0x92);  // Kernel Data Segment
    create_segment_descriptor(&gdt[3], 0, 64 * 1024 * 1024, 0xFA);  // User Code Segment
    create_segment_descriptor(&gdt[4], 0, 64 * 1024 * 1024, 0xF2);  // User Data Segment

    printf("Loading gdt pointer into gdtr...\n");
    setGdt(&gdt_ptr);
    printf("Reloading segments...\n");
    reloadSegments();
}

void create_segment_descriptor(segment_descriptor_struct* target, uint32_t base, uint32_t limit, uint8_t access_rights) {
    if(limit <= 65536) {
        target->flags_limit_hi = 0x40;
    } else {
        if((limit & 0xFFF) != 0xFFF) 
            limit = (limit >> 12) - 1;
        else 
            limit = limit >> 12;
        
        target->flags_limit_hi = 0xC0;
    }

    // Base
    target->base_lo         = base & 0xFFFF;
    target->base_hi         = (base >> 16) & 0xFF;
    target->base_xhi        = (base >> 24) & 0xFF;

    // Limit
    target->limit_lo        = limit & 0xFFFF;
    target->flags_limit_hi |= (limit >> 16) & 0x0F;

    // Access
    target->access_rights   = access_rights;
}