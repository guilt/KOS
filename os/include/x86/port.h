#ifndef PORT_H
#define PORT_H

#ifndef ASM
#include <types.h>
#endif /* ASM */

#define PORT_PIC_MASTER_CMD  0x20
#define PORT_PIC_MASTER_DATA 0x21
#define PORT_PIC_SLAVE_CMD   0xA0
#define PORT_PIC_SLAVE_DATA  0xA1

#ifndef ASM
#define inb inb_impl
#define inw inw_impl
#define inl inl_impl

/* Inputs a value through a port */
uint8 inb_impl(uint16 port);

/* Inputs a value through a port */
uint16 inw_impl(uint16 port);

/* Inputs a value through a port */
uint32 inl_impl(uint16 port);

#define outb outb_impl
#define outw outw_impl
#define outl outl_impl

/* Outputs a value through a port */
void outb_impl(uint16 port, uint8 value);

/* Outputs a value through a port */
void outw_impl(uint16 port, uint16 value);

/* Outputs a value through a port */
void outl_impl(uint16 port, uint32 value);

#endif /* ASM */

#endif /* PORT_H */
