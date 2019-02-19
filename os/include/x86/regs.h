#ifndef REGS_H
#define REGS_H

#include <mem.h>

#ifndef ASM

#pragma pack(push)
#pragma pack(1)

/* Register Params, Context Switch */
typedef struct _regs {
   uint16 gs, es, fs, ds;
   uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32 irq, intr, err_code;
   uint32 eip, cs, eflags, useresp, ss;
} regs;

#pragma pack(pop)

#endif /* ASM */

#endif /* REGS_H */
