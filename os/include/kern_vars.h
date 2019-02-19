#ifndef KERN_VARS_H
#define KERN_VARS_H

#include <kern_mem.h>
#include <arch_vars.h>

#pragma pack(push)
#pragma pack(1)

/* System Variables */
typedef struct _kern_vars {
	uint32 physmem;
	kmem_map *free_map;
	kmem_map *used_map;
	arch_vars *avars;
} kern_vars;

extern kern_vars *vars;

#pragma pack(pop)

#endif /* KERN_VARS_H */
