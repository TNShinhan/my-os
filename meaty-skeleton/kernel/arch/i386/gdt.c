#include <kernel/gdt.h>

// Define as static/global since the GDT on the stack may be overwritten
static GlobalDescriptorTable gdt;

void load_gdt_segments() {
    printf("Creating gdt...\n");
    create_gdt();

    uint16_t limit = sizeof(GlobalDescriptorTable) - 1;
    uint32_t base  = (uint32_t)&gdt;

    printf("Loading gdt pointer into gdtr...\n");
    setGdt(limit, base);
    printf("Reloading segments...\n");
    reloadSegments();
}

void create_gdt() {
    create_segment_descriptor(&gdt.null_segment, 0, 0, 0);
    create_segment_descriptor(&gdt.kernel_code_segment, 0, 64 * 1024 * 1024, 0x9A);
    create_segment_descriptor(&gdt.kernel_data_segment, 0, 64 * 1024 * 1024, 0x92);
}

void create_segment_descriptor(SegmentDescriptor* target, uint32_t base, uint32_t limit, uint8_t access_rights) {
    if(limit <= 65536) {
        target->flags_limit_hi = 0x40;
    } else {
        if((limit & 0xFFF) != 0xFFF) 
            limit = (limit >> 12) - 1;
        else 
            limit = limit >> 12;
        
        target->flags_limit_hi = 0xC0;
    }

    target->limit_lo        = limit & 0xFFFF;
    target->base_lo         = base & 0xFFFF;
    target->base_hi         = (base >> 16) & 0xFF;
    target->access_rights   = access_rights;
    target->flags_limit_hi |= (limit >> 16) & 0x0F;
    target->base_xhi        = (base >> 24) & 0xFF;
}