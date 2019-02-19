/* entry.S - Kernel entry point */

#define ASM	1
#include <multiboot.h>
#include <mem.h>
	
	.text
	.globl	start, _start, __start
start:
_start:
__start:
	jmp	multiboot_entry

	/* Align 64 bits boundary.  */
	.align	8
	
	/* Multiboot header.  */
multiboot_header:
	/* magic */
	.long	MULTIBOOT_HEADER_MAGIC
	/* flags */
	.long	MULTIBOOT_HEADER_FLAGS
	/* checksum */
	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
#ifndef __ELF__
	/* header_addr */
	.long	multiboot_header
	/* load_addr */
	.long	multiboot_entry
	/* load_end_addr */
	.long	bss_start
	/* bss_end_addr */
	.long	bss_end
	/* entry_addr */
	.long	start
#endif /* ! __ELF__ */

	/* Our stack area.  */
	.globl protmode_stack,_protmode_stack
protmode_stack_start:
_protmode_stack_start:
	.fill PROTMODE_STACK_SIZE, 1, 0
protmode_stack:
_protmode_stack:
	.globl protmode_stack_ptr,_protmode_stack_ptr
protmode_stack_ptr:
_protmode_stack_ptr:
	.long PROTMODE_STACK

multiboot_entry:
	/* Initialize the stack pointer.  */
	movl	(protmode_stack_ptr), %esp
	movl    %esp,%ebp
	/* Reset EFLAGS.  */
	pushl	$0
	popf
	/* Push the pointer to the Multiboot information structure.  */
	pushl	%ebx
	/* Push the magic value.  */
	pushl	%eax
	/* Now enter the protected mode C main function...  */
	call	cmain
loop:	hlt
	jmp	loop
