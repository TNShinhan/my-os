; External to this file b/c its's the name of the main C func in 'kernel.c'
.extern kernel_main

; Declare 'start' label as global, since linker will need to know where it is
.global start

; Our bootloader, GRUB, needs to know some basic information about our kernel before it can boot it.
; We give GRUB this information using a standard known as 'Multiboot'.
; To define a valid 'Multiboot header' that will be recognised by GRUB, we need to hard code some
; constants into the executable. The following code calculates those constants.
.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, (1 << 0) | (1 << 1)
; Finally, calculate the checksum
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

; Define our Multiboot header
.section .multiboot
    .align 4 ; Allign following data on multiple of 4 bytes (32-bits)
    .long MB_MAGIC
    .long MB_FLAGS
    .long MB_CHECKSUM

; This section contains data initialized to zeroes when kernel is loaded
.section .bss
    ; C/C++ code will need a stack to run. Here, we allocate 4096 bytes
    .align 16       ; Complies and satisfies with ABI and CPU
    stack_bottom:
        ; We can expland this later if we want a larger stack
        .skip 4096  ; Reserve 4k stack
    stack_top:

/*
The linker script specifies _start as the entry point to the kernel and the
bootloader will jump to this position once the kernel has been loaded. It
doesn't make sense to return from this function as the bootloader is gone.
*/
.section .text
    start:
        /* 
        First thing's first: we want to set up an environment that's ready to run C code.
		C is very relaxed in its requirements: All we need to do is to set up the stack.
        On x86, the stack grows downward, this is why we start at the top
        */
        mov $stack_top, %esp ; Set the stack pointer to top of stack

        ; We can now call our main C function
        call kernel_main

        ; If kernel's C code ever returns, hang the CPU
        hang:
            cli      ; Disable CPU interrupts
            hlt      ; Halt the CPU
            jmp hang ; If that didn't work, loop and try again