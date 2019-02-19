/* cmem.c - Memory Routines */

#include <minilib.h>
#include <mem.h>

extern descriptortable gdt;
extern int realstart, realend;

void printselectors() {
    selector sr;
#define printregister(s) asm("movw %%"#s",%%ax\n\t":"=a"(sr)); printf("%s ",#s); printf("Selector: Level: %d, Table: %s, Index: %d\n",selectorpriv(sr),(selectortable(sr)?"LDT":"GDT"),selectorindex(sr));
    printregister(cs);
    printregister(ds);
    printregister(es);
    printregister(fs);
    printregister(gs);
    printregister(ss);
#undef printregister
}

void printdescriptortable(descriptortable *table) {
    uint16 entries=(table->size+1)/sizeof(descriptor);
    uint16 entry=0;
    printf("Descriptor Table at: 0x%x, Size: %d\n",table->descptr, (table->size+1));
    if(!entries) return;
    for(entry=0; entry<entries; ++entry) {
       descriptor *desc=table->descptr+entry;
       printf("Segment %d: ",entry);
       if(!(*desc).acc.present) {
	   printf("Unavailable \n");
           continue;
       }
       printf("0x%x + 0x%x, Level: %d, Mode: %dbit",descriptorbase(*desc),descriptorlimit(*desc),(*desc).acc.priv,descriptormode(*desc));
       printf(", Type: ");
       if(!(*desc).acc.user) {
	   printf("System ");
       } else { 
         if((*desc).acc.ext) {
             printf("Code ");
             if(!(*desc).acc.extdirprivlevel) {
                 printf("[IgnorePriv] ");
             }
             if(!(*desc).acc.readwrite) {
                 printf("[NoExecute] ");
             }
         } else {
             printf("Data ");
             if((*desc).acc.extdirprivlevel) {
                 printf("[Stack] ");
             }
             if(!(*desc).acc.readwrite) {
                 printf("[ReadOnly] ");
             }
         }
       }
       if((*desc).acc.user&&(*desc).acc.accessedinuser) {
	   printf("[AccessedInUser] ");
       }
       if(!(*desc).availableforsystem) {
           printf("[AvailableForSystem] ");
       }
       printf("\n");
    }
}

int reloc(int addr){
    return (addr-realstart+REALMODE_START);
}

void init_realmode_params(){
   descriptortable *realgdt=&gdt;
    memcpy((void *)REALMODE_START, (void *)realstart, realend-realstart);
    realgdt=RELOC(&gdt);
    realgdt->descptr=RELOC(gdt.descptr);
}

void init_protmode_params(){
    descriptortable current_gdt;
    getdescriptortable(&current_gdt);
    gdt.size=current_gdt.size;
    memcpy(gdt.descptr,current_gdt.descptr,gdt.size+1);
    setdescriptortable(&gdt);
}
