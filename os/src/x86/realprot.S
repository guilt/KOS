/* realport.S - real/protected mode code */

#define ASM	1
#include <mem.h>
#include <intr.h>

	.text
        .code16
realstart_ptr:
_realstart_ptr:

	.align 8
realmode_bootsect:
_realmode_bootsect:
	.fill REALMODE_BSECT_SIZE, 1, 0

realmode_stack_start:
_realmode_stack_start:
	.fill REALMODE_STACK_SIZE, 1, 0
realmode_stack:
_realmode_stack:

realmode_entry:
_realmode_entry:
	movw $(SEG_REAL),%ax
	movw %ax,%ss
	movw %ax,%gs
	movw %ax,%fs
	movw %ax,%es
	movw %ax,%ds
	movw $(REALMODE_STACK),%ax
	movw %ax,%sp
	/* call enable_interrupts16 */
	/* Do realmode stuff here */

enter_protmode:
_enter_protmode:
	/* call disable_interrupts16 */
	movl $RELOC(idt), %eax
	lidt (%eax)
        movl $RELOC(gdt), %eax
	lgdt (%eax)
        movl %cr0, %eax
	orl  $(CR0_PE),%eax
	movl %eax,%cr0
	xorl %eax,%eax
        ljmpl $(SEG_KERN_CODE_SEL),$realmode_to_protmode

enable_interrupts16:
_enable_interrupts16:
	sti
	ret

disable_interrupts16:
_disable_interrupts16:
	cli
	ret

	.code32
realmode_to_protmode:
_realmode_to_protmode:

	.extern protmode_stack_ptr
	.extern enable_interrupts
protmode_entry:
_protmode_entry:
	/* Initialize the stack pointer.  */
	movw $(SEG_KERN_DATA_SEL),%ax
	movw %ax,%ss
	movw %ax,%gs
	movw %ax,%fs
	movw %ax,%es
	movw %ax,%ds
	movl (protmode_stack_ptr), %esp
	popl %ebp
        popf
	ret

	.globl	enter_realmode, _enter_realmode
	.extern disable_interrupts
enter_realmode:
_enter_realmode:
	pushf
	call disable_interrupts
	pushl %ebp
	movl %esp, (protmode_stack_ptr)
	movl $realidt,%eax
	lidt (%eax)
        ljmpl $(SEG_KERN_PRCODE_SEL),$RELOC(protmode_to_realmode)

protmode_to_realmode:
_protmode_to_realmode:
        movl %cr0, %eax
	xorl $(CR0_PE),%eax
	movl %eax,%cr0
	xorl %eax,%eax
        ljmpl $(SEG_REAL),$RELOC(realmode_entry)

	.globl realidt, _realidt
realidt:
_realidt:
        .word MAX_INTERRUPTS
        .long 0

	.align 8
gdttable:
_gdttable:
	/* Allocate some bytes here, set them in protected mode code */
        .fill 1024, 8, 0

	.globl gdt, _gdt
	.align 8
gdt:
_gdt:
        .word 0
	.long gdttable
realend_ptr:
_realend_ptr:

	.globl realstart, _realstart
realstart:
_realstart:
	.long realstart_ptr

	.globl realend, _realend
realend:
_realend:
	.long realend_ptr

	.align 8
idttable:
_idttable:
	.fill 256, 8, 0

	.globl idt, _idt
	.align 8
idt:
_idt:
        .word 0
	.long idttable

	.globl hl_intr_handlers, _hl_intr_handlers
	.align 8
hl_intr_handlers:
_hl_intr_handlers:
	.fill 256, 4, 0
