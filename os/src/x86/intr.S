/* intr.S - Interrupt Routines */

#define ASM	1
#include <intr.h>
	
.text

.globl	enable_interrupts, _enable_interrupts
enable_interrupts:
_enable_interrupts:
	sti
	ret

.globl	disable_interrupts, _disable_interrupts
disable_interrupts:
_disable_interrupts:
	cli
	ret

.globl	setgatedescriptortable, _setgatedescriptortable
setgatedescriptortable:
_setgatedescriptortable:
	movl 4(%esp), %eax
	lidt (%eax)
	ret

.globl	getgatedescriptortable, _getgatedescriptortable
getgatedescriptortable:
_getgatedescriptortable:
	movl 4(%esp), %eax
	sidt (%eax)
	ret
