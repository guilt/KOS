/* kernel.c - the C part of the kernel */

#include <ver.h>
#include <aver.h>
#include <multiboot.h>
#include <minilib.h>
#include <mem.h>
#include <kern_vars.h>
#include <arch.h>

int kernel_inited=0;

void cmain (uint32 magic, uint32 addr)
{
  if(!kernel_inited) {
    cls();
    printf ("%s - %d.%d (%s)\n", VER_NAME, VER_MINOR, VER_MAJOR, AVER_NAME);
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
      printf ("Non-multi boot image.\n", (unsigned) magic);
    } else {
      printf ("Multi-boot initialization.\n", (unsigned) magic);
      multiboot_init(addr);
    }
    printf("Memory available: %u\n",vars->physmem);
    arch_init();
    ++kernel_inited;
  }
  arch_quit();
}
