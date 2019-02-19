/* arch.c - the C part of the kernel, architecture specific. */

#include <ver.h>
#include <aver.h>
#include <multiboot.h>
#include <minilib.h>
#include <mem.h>
#include <intr.h>
#include <kern_vars.h>
#include <arch.h>

void x86_init()
{

	init_protmode_params();
	#ifdef REALMODE_GIMMICK 
    	init_realmode_params();
	#endif
	{
		descriptortable current_gdt;
		getdescriptortable(&current_gdt);
		setdescriptortable(&current_gdt);
		printdescriptortable(&current_gdt);
       		printselectors();
	}
	init_interrupts();
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");

        /* Code kept for enlightening purposes */
#ifdef REALMODE_GIMMICK 
	enter_realmode();
	printf("Back from the dead!\n");
#endif
}

void x86_quit()
{
	while(1);
}
