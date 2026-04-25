// ; INTEL SYNTAX
// ; ------------
// gdtr DW 0 ; Declare an 2-byte (word) unitialized variable, referred by location as gdtr and then initialize it with 0 
//           ; which reserves the 16-bit space required for GDT limit
//      DD 0 ; Declare an 4-byte (double word) uninitialized space and then initialize it with 0,
//           ; reserving 32-bit space required for the GDT offset (linear address of GDT)

// setGdt:
//     MOV  AX, [esp + 4]   ; Grab the limit parameter stored at the top of the stack (lower address) + 4 bytes (higher address now), store into AX register (16-bits)
//     MOV  [gdtr], AX      ; Store what's in AX at where gdtr is
//     MOV  EAX, [esp + 4]  ; Grab base parameter stored at the top of the stack + 8 bytes, store into EAX register (32-bits)
//     MOV  [gdtr + 2], EAX ; Store what's in EAX at where gdtr is + 2 bytes
//     LGDT [gdtr]
//     RET

// reloadSegments:
//     ; Reload CS register containing code selector:
//     JMP 0x08:.reload_CS ; 0x08 is a stand-in for your code segment

// .reload_CS:
//     ; Reload data segment registers:
//     MOV AX, 0x10 ; 0x10 is a stand-in for your data segment
//     MOV DS, AX
//     MOV ES, AX
//     MOV FS, AX
//     MOV GS, AX
//     MOV SS, AX
//     RET
// ; ------------

// ; Data section
.section .data
.align 4
gdtr:
    .short 0
    .long 0

// ; Code section
.section .text
.global setGdt
.type setGdt, @function
setGdt:
    movw 4(%esp), %ax
    movw %ax, gdtr
    movl 8(%esp), %EAX
    movl %eax, gdtr+2
    lgdt gdtr
    ret

// Flush old segment registers from the bootloader with new segments from the gdt
.global reloadSegments
.type reloadSegments, @function
reloadSegments:
    // Far jump to update CS register to 0x08 (Kernel Code Segment)
    ljmp $0x08, $.reload_CS

.reload_CS:
    // Update data segment registers to 0x10 (Kernel Data Segment)
    movw $0x10, %ax      
    movw %ax, %ds        
    movw %ax, %es        
    movw %ax, %fs        
    movw %ax, %gs        
    movw %ax, %ss        
    ret
