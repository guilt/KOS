/* mem.S - Memory Routines */

#define ASM	1
#include <mem.h>
	
.text

.globl	setdescriptortable, _setdescriptortable
setdescriptortable:
_setdescriptortable:
	movl 4(%esp), %eax
	lgdt (%eax)
	ljmpl $(SEG_KERN_CODE_SEL), $lgdt_done
lgdt_done:
	movw $(SEG_KERN_DATA_SEL), %ax
	movw %ax,%ss
	movw %ax,%gs
	movw %ax,%fs
	movw %ax,%es
	movw %ax,%ds
	ret

.globl	getdescriptortable, _getdescriptortable
getdescriptortable:
_getdescriptortable:
	movl 4(%esp), %eax
	sgdt (%eax)
	ret
