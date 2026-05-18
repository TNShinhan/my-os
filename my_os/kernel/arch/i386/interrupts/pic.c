#include <kernel/pic.h>

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT    0X21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT    0XA1

void init_pic() {
    // initialization control word 1
    outPortB(PIC1_COMMAND_PORT, 0x11);
    outPortB(PIC2_COMMAND_PORT, 0x11);

    // initialization control word 2 (vector offsets)
    outPortB(PIC1_DATA_PORT, 0x20);
    outPortB(PIC2_DATA_PORT, 0x28);

    // initialization control word 3
    outPortB(PIC1_DATA_PORT, 0x04);       // tell pic1 that it has a salve at IRQ2
    outPortB(PIC2_DATA_PORT, 0x02);       // tell pic2 its cascade identity

    // initialization control word 4
    outPortB(PIC1_DATA_PORT, 0x01);
    outPortB(PIC2_DATA_PORT, 0x01);

    // clear data registers
    outPortB(PIC1_DATA_PORT, 0x0);
    outPortB(PIC2_DATA_PORT, 0x0);
}