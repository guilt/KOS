#ifndef MEM_H
#define MEM_H

#ifndef ASM
#include <types.h>
#endif /* ASM */

#define SEGMENTS 5

#define MAKESEG(index, priv, table) ((priv)|((table)<<2)|((index)<<3))
#define selectortable(sel) (((sel)&0x4)>>2)
#define selectorpriv(sel) ((sel)&0x3)
#define selectorindex(sel) (((sel)&0xfff8)>>3)

/* Control Register Flags */
#define CR0_PE 0x00000001

/* Table */
#define GDT_TABLE 0
#define LDT_TABLE 1

/* Flat Segmented Model: Base - 0x00000000, Limit - 0xffffffff */
#define SEG_REAL        0
#define SEG_KERN_UNUSED 0

/* Kernel Code */
#define SEG_KERN_CODE   1
#define SEG_KERN_CODE_PRIV 0
#define SEG_KERN_CODE_SEL MAKESEG(SEG_KERN_CODE, SEG_KERN_CODE_PRIV, GDT_TABLE)

/* Kernel Data */
#define SEG_KERN_DATA   2
#define SEG_KERN_DATA_PRIV 0
#define SEG_KERN_DATA_SEL MAKESEG(SEG_KERN_DATA, SEG_KERN_DATA_PRIV, GDT_TABLE)

/* Kernel Protected-Real Code */
#define SEG_KERN_PRCODE 3
#define SEG_KERN_PRCODE_PRIV 0
#define SEG_KERN_PRCODE_SEL MAKESEG(SEG_KERN_PRCODE, SEG_KERN_PRCODE_PRIV, GDT_TABLE)

/* Kernel Protected-Real Data */
#define SEG_KERN_PRDATA   4
#define SEG_KERN_PRDATA_PRIV 0
#define SEG_KERN_PRDATA_SEL MAKESEG(SEG_KERN_PRDATA, SEG_KERN_PRDATA_PRIV, GDT_TABLE)

/* Real Mode Values */
#define REALMODE_START (0x7c00)
#define REALMODE_BSECT_SIZE 512
#define REALMODE_STACK_START (REALMODE_START+REALMODE_BSECT_SIZE)
#define REALMODE_STACK_SIZE 512
#define REALMODE_STACK (REALMODE_STACK_START+REALMODE_STACK_SIZE)
#define REALMODE_CODE  (REALMODE_STACK)

/* Protected Mode Values */
#define PROTMODE_START (0x100000)
#ifdef ASM
#define PROTMODE_STACK_START	(protmode_stack)
#else
extern int protmode_stack;
#define PROTMODE_STACK_START	((int)&protmode_stack)
#endif /* ASM */
#define PROTMODE_STACK_SIZE	16384
#define PROTMODE_STACK	(PROTMODE_STACK_START+PROTMODE_STACK_SIZE)
#define PROTMODE_CODE	(PROTMODE_STACK)

#ifdef ASM
#define RELOC(addr) ((addr)-realstart_ptr+REALMODE_START)
#endif /* ASM */

#ifndef ASM
#define RELOC(addr) ((void *)reloc((int)(addr)))
#undef PROTMODE_STACK_START
#define PROTMODE_STACK_START	(&protmode_stack)

#pragma pack(push)
#pragma pack(1)

#define privlevel(x) bitfield(priv,2)

typedef uint16 selector;

typedef struct _access {
    bitfield(accessedinuser,1);
    bitfield(readwrite,1);
    bitfield(extdirprivlevel,1);
    bitfield(ext,1);
    bitfield(user,1);
    privlevel(priv);
    bitfield(present,1);
} access;

#define descriptorgranularity(d) ((d).granularity?4096:1)
#define descriptormode(d) ((d).datamode?32:16)
#define descriptorbase(d) ((paddr)(((d).base2<<24)|(d).base1))
#define descriptorlimit(d) ((paddr)(((d).limit2<<16)|(d).limit1)*descriptorgranularity(d))

typedef struct _descriptor {
    bitfield(limit1,16);
    bitfield(base1,24);
    access acc;
    bitfield(limit2,4);
    bitfield(availableforsystem,1);
    bitfield(dummy,1);
    bitfield(datamode,1);
    bitfield(granularity,1);
    bitfield(base2,8);
} descriptor;

typedef struct _descriptortable {
    uint16 size;
    descriptor *descptr;
} descriptortable;

#pragma pack(pop)

/* Gets the descriptor table into the memory pointed by address. */
void getdescriptortable(descriptortable *table);

/* Sets the descriptor table by the memory pointed by address, and makes a jump to SEG_KERN_PRCODE. */
void setdescriptortable(descriptortable *table);

/* Prints the descriptor table entries in human readable format. */
void printdescriptortable(descriptortable *table);

/* Prints the current descriptor selectors in human readable format. */
void printselectors();

/* Relocates address wrt to real mode */
int reloc(int addr);

/* Copies realmode code and data into relocated address */
void init_realmode_params();

/* Sets kernel's descriptor table */
void init_protmode_params();

#endif /* ASM */

#endif /* MEM_H */
