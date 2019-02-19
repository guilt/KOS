#ifndef INTR_H
#define INTR_H

#include <regs.h>
#include <mem.h>

#define MAX_INTERRUPTS 256

#define ICW1_ICW4	0x01 /* ICW4/Not Needed */
#define ICW1_SINGLE	0x02 /* Single/Cascade mode */
#define ICW1_INTERVAL4	0x04 /* Call Address Interval 4/8 */
#define ICW1_LEVEL	0x08 /* Level/Edge Triggered */
#define ICW1_INIT	0x10 /* Initialized/Not */
#define ICW1_RESET      0x20 /* Reset */

#define ICW4_8086	0x01 /* 8086-88/MCS80-85) mode */
#define ICW4_AUTO	0x02 /* Auto/Normal EOI */
#define ICW4_BUF_SLAVE	0x08 /* Buffered Mode Slave */
#define ICW4_BUF_MASTER	0x0C /* Buffered Mode Master */
#define ICW4_SFNM	0x10 /* Special Fully Nested/Not */

#define ORIG_MASTER_OFFSET 0
#define ORIG_SLAVE_OFFSET  112

#define REMAP_IRQ_COUNT     8  					  /* 8 Per Controller */
#define REMAP_MASTER_OFFSET 32 					  /* Remap IRQ 0-7  to 32-39 */
#define REMAP_SLAVE_OFFSET  (REMAP_MASTER_OFFSET+REMAP_IRQ_COUNT) /* Remap IRQ 8-15 to 40-47 */
#define REMAP_MASTER_PIN    4
#define REMAP_SLAVE_PIN     2

#ifndef ASM

#pragma pack(push)
#pragma pack(1)

#define gatedescriptorbase(i) ((paddr)(((i).base2<<16)|(i).base1))

typedef struct _gatedescriptor {
    bitfield(base1,16);
    selector codesel;
    bitfield(dwordcount,5);
    bitfield(dummy,3);
    access acc;
    bitfield(base2,16);
} gatedescriptor;

typedef struct _gatedescriptortable {
    uint16 size;
    gatedescriptor *descptr;
} gatedescriptortable;

#pragma pack(pop)

typedef uint8 intr_number;
typedef void (*intr_function)(regs *reg);

/* Gets the gate descriptor table into the memory pointed by address. */
void getgatedescriptortable(gatedescriptortable *table);

/* Sets the gate descriptor table by the memory pointed by address. */
void setgatedescriptortable(gatedescriptortable *table);

/* Sets interrupt function for a given interrupt */
void set_intr_function(intr_number intr, intr_function func);

/* Gets interrupt function for a given interrupt */
intr_function get_intr_function(intr_number intr);

/* Enable interrupts */
void enable_interrupts();

/* Disable interrupts */
void disable_interrupts();

/* Initialize Interrupts */
void init_interrupts();

#endif /* ASM */

#endif /* INTR_H */
