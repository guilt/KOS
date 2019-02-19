#ifndef ARCH_VARS_H
#define ARCH_VARS_H

#include <types.h>
#include <mem.h>

#pragma pack(push)
#pragma pack(1)

typedef struct _x86_vars {
	int protected_mode_inited;
	int real_mode_inited;
} x86_vars;

#pragma pack(pop)

#define arch_vars x86_vars

#endif /* ARCH_VARS_H */
