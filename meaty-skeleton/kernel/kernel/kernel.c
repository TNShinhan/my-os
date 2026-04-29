#include <stdio.h>
#include <kernel/gdt.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	init_gdt_segments();
	printf("Hello, kernel World!\n");
}
