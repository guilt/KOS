/* multiboot.h - the header for Multiboot */

/* The magic number for the Multiboot header.  */
#define MULTIBOOT_HEADER_MAGIC		0x1badb002

/* The flags for the Multiboot header.  */
#ifdef __ELF__
# define MULTIBOOT_HEADER_FLAGS		0x00000003
#else
# define MULTIBOOT_HEADER_FLAGS		0x00010003
#endif

/* The magic number passed by a Multiboot-compliant boot loader.  */
#define MULTIBOOT_BOOTLOADER_MAGIC	0x2badb002

#ifndef ASM
#include <types.h>

/* The Multiboot header.  */
typedef struct multiboot_header
{
  uint32 magic;
  uint32 flags;
  uint32 checksum;
  uint32 header_addr;
  uint32 load_addr;
  uint32 load_end_addr;
  uint32 bss_end_addr;
  uint32 entry_addr;
} multiboot_header_t;

/* The symbol table for a.out.  */
typedef struct aout_symbol_table
{
  uint32 tabsize;
  uint32 strsize;
  uint32 addr;
  uint32 reserved;
} aout_symbol_table_t;

/* The section header table for ELF.  */
typedef struct elf_section_header_table
{
  uint32 num;
  uint32 size;
  uint32 addr;
  uint32 shndx;
} elf_section_header_table_t;

/* The Multiboot information.  */
typedef struct multiboot_info
{
  uint32 flags;
  uint32 mem_lower;
  uint32 mem_upper;
  uint32 boot_device;
  uint32 cmdline;
  uint32 mods_count;
  uint32 mods_addr;
  union
  {
    aout_symbol_table_t aout_sym;
    elf_section_header_table_t elf_sec;
  } u;
  uint32 mmap_length;
  uint32 mmap_addr;
} multiboot_info_t;

/* The module structure.  */
typedef struct module
{
  uint32 mod_start;
  uint32 mod_end;
  uint32 string;
  uint32 reserved;
} module_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
   but no size.  */
typedef struct memory_map
{
  uint32 size;
  uint32 base_addr_low;
  uint32 base_addr_high;
  uint32 length_low;
  uint32 length_high;
  uint32 type;
} memory_map_t;

void multiboot_init(uint32 addr);

#endif /* ! ASM */
