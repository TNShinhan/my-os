#include <stdio.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/tty.h>

extern void crash_me();

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	init_gdt();
	init_idt();
	crash_me();
}
