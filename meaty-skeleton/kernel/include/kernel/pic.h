#ifndef __PIC_H
#define __PIC_H

void init_pic();

extern void outPortB(uint16_t port, uint8_t value);

#endif