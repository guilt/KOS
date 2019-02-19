/* cintr.c - Interrupt Routines */

#include <minilib.h>
#include <intr.h>
#include <port.h>

/* Low level Interrupt Handler Table */
extern gatedescriptortable idt;
extern uint32* intr_handlers;
extern intr_function *hl_intr_handlers;

/* Default Interrupt Handler */
static void default_intr_handler(regs *reg) {
	printf("Default Interrupt: %d",reg->intr);
	if(reg->intr != reg->irq) 
		printf(" IRQ: %d",reg->irq);
	printf("\n");
}

/* Interrupt Stub */
void hl_intr_handler_stub(regs reg) {
	if(hl_intr_handlers[reg.intr]!=NULL) {
		hl_intr_handlers[reg.intr](&reg);
	}
	if(reg.intr>=REMAP_MASTER_OFFSET) {
		if(reg.intr<REMAP_SLAVE_OFFSET) {
			outb(PORT_PIC_MASTER_CMD , ICW1_RESET);
		} else if(reg.intr<(REMAP_SLAVE_OFFSET+REMAP_IRQ_COUNT)) {
			outb(PORT_PIC_SLAVE_CMD  , ICW1_RESET);
		}
	}
}

/* Sets interrupt function for a given interrupt */
void set_intr_function(intr_number intr, intr_function function) {
	gatedescriptor *desc;
	uint32 fnptr=NULL;
	intr_number max_intr=0;
	if(intr>=MAX_INTERRUPTS) 
		return;
        desc=idt.descptr+intr;
	max_intr=(idt.size+1)/sizeof(gatedescriptor);
	if(intr>max_intr)
		max_intr=intr;
	desc->dwordcount=0; desc->dummy=0;
	desc->acc.accessedinuser=0;
	if(function!=NULL) {
        	fnptr=intr_handlers[intr];
		desc->acc.readwrite=1; desc->acc.extdirprivlevel=1; desc->acc.ext=1; desc->acc.present=1;
	} else {
		desc->acc.readwrite=0; desc->acc.extdirprivlevel=0; desc->acc.ext=0; desc->acc.present=0;
	}
	hl_intr_handlers[intr]=function;
	desc->base2=(uint16)(fnptr>>16); desc->base1=(uint16)fnptr;
        desc->acc.user=0; desc->acc.priv=SEG_KERN_CODE_PRIV;
        desc->codesel=SEG_KERN_CODE_SEL;
	idt.size=(uint16)(((max_intr+1)*sizeof(gatedescriptor))-1);
	setgatedescriptortable(&idt);
}

/* Gets interrupt function for a given interrupt */
intr_function get_intr_function(intr_number intr) {
	if(intr>=MAX_INTERRUPTS)
		return (intr_function)NULL;
	return hl_intr_handlers[intr];
}

/* Initialize APIC */
static void init_apic() {
	uint8 master_val=inb(PORT_PIC_MASTER_DATA);
	uint8 slave_val =inb(PORT_PIC_SLAVE_DATA );

	outb(PORT_PIC_MASTER_CMD , ICW1_INIT | ICW1_ICW4);
	outb(PORT_PIC_SLAVE_CMD  , ICW1_INIT | ICW1_ICW4);

	outb(PORT_PIC_MASTER_DATA, REMAP_MASTER_OFFSET);
	outb(PORT_PIC_SLAVE_DATA,  REMAP_SLAVE_OFFSET);

	outb(PORT_PIC_MASTER_DATA, REMAP_MASTER_PIN);
	outb(PORT_PIC_SLAVE_DATA,  REMAP_SLAVE_PIN);

	outb(PORT_PIC_MASTER_DATA, ICW4_8086);
	outb(PORT_PIC_SLAVE_DATA,  ICW4_8086);

	outb(PORT_PIC_MASTER_DATA, master_val);
	outb(PORT_PIC_SLAVE_DATA , slave_val);
}

/* Initialize Interrupts */
void init_interrupts() {
	uint16 intr;
	disable_interrupts();
	init_apic();
	for(intr=0;intr<MAX_INTERRUPTS;++intr) {
		set_intr_function(intr,NULL);
	}
	for(intr=0;intr<(REMAP_SLAVE_OFFSET+REMAP_IRQ_COUNT);++intr) {
		set_intr_function(intr,default_intr_handler);
	}
	enable_interrupts();
}
