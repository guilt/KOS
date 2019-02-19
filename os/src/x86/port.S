/* port.S - Port Routines */

#define ASM	1
#include <port.h>
	
.text

.globl	inb_impl, _inb_impl
inb_impl:
_inb_impl:
	movl 4(%esp), %edx
	inb %dx,%al
	ret

.globl	inw_impl, _inw_impl
inw_impl:
_inw_impl:
	movl 4(%esp), %edx
	inw %dx,%ax
	ret

.globl	inl_impl, _inl_impl
inl_impl:
_inl_impl:
	movl 4(%esp), %edx
	inl %dx,%eax
	ret

.globl	outb_impl, _outb_impl
outb_impl:
_outb_impl:
	movl 8(%esp), %eax
	movl 4(%esp), %edx
	outb %al,%dx
	ret

.globl	outw_impl, _outw_impl
outw_impl:
_outw_impl:
	movl 8(%esp), %eax
	movl 4(%esp), %edx
	outw %ax,%dx
	ret

.globl	outl_impl, _outl_impl
outl_impl:
_outl_impl:
	movl 8(%esp), %eax
	movl 4(%esp), %edx
	outl %eax,%dx
	ret

