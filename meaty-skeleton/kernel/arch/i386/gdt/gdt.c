#include <kernel/gdt.h>

#define     GDT_CODE_SEGMENT               0x08

// Define as static/global since the GDT on the stack may be overwritten
gdt_entry gdt[5];
gdt_descriptor gdt_ptr = {sizeof(gdt) - 1, (uint32_t)gdt};

void init_gdt() {
    set_gdt_entry(0, 0, 0, 0);                    // Unused segment
    set_gdt_entry(1, 0, 64 * 1024 * 1024, 0x9A);  // Kernel Code Segment
    set_gdt_entry(2, 0, 64 * 1024 * 1024, 0x92);  // Kernel Data Segment
    set_gdt_entry(3, 0, 64 * 1024 * 1024, 0xFA);  // User Code Segment
    set_gdt_entry(4, 0, 64 * 1024 * 1024, 0xF2);  // User Data Segment

    setGdt(&gdt_ptr);
    reloadSegments();
}

void set_gdt_entry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access_rights) {
    gdt_entry* target = &gdt[num];

    if(limit <= 0xFFFFF) {
        // Fits perfectly in 20 bits. Use byte granularity (G=0)
        target->flags_limit_hi = 0x40;   // Limit is in 1-byte sized blocks
    } else {
        // Too big for 20 bits. Convert to 4KB pages (G=1)
        if((limit & 0xFFF) != 0xFFF) 
            limit = (limit >> 12) - 1;   // The (- 1) ensures that we strictly round down to the nearest safe page boundary
        else 
            limit = limit >> 12;
        
        target->flags_limit_hi = 0xC0;  // Limit is in 4KiB blocks
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