#ifndef KERN_MEM_H
#define KERN_MEM_H

#include <arch.h>
#include <types.h>
#include <mem.h>

#pragma pack(push)
#pragma pack(1)

/* Memory Allocation Map */
typedef struct _kmem_map {
	uint32 start;
	uint32 limit;
	uint32 used;	
	struct _kmem_map *next;
} kmem_map;

void *kmalloc(uint32 size);
void kfree(void *ptr);

#pragma pack(pop)

#endif /* KERN_MAP_H */
