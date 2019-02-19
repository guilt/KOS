ENTRY(start)
LOADADDRESS = 1048576;
DATAADDRESS = 4194304;
SECTIONS
{ 
  . = LOADADDRESS;
  .text LOADADDRESS : AT(LOADADDRESS)
  {
	text_start = .; _text_start = .; __text_start = .;
	*(.text)
	*(.rodata)
	. = ALIGN(4096);
	text_end = .; _text_end = .; __text_end = .;
  }
  .data : AT(LOADADDRESS + data_start - text_start)
  {
	data_start = .; _data_start = .; __data_start = .;
	*(.data)
	. = ALIGN(4096);
	data_end = .; _data_end = .; __data_end = .;
  }
  .bss : AT(LOADADDRESS + bss_start - text_start)
  {
	bss_start = .; _bss_start = .; __bss_start = .;
	*(.bss)
	*(.common)
	. = ALIGN(4096);
	bss_end = .; _bss_end = .; __bss_end = .;
  }
  . = DATAADDRESS;
  kernel_vars = .; _kernel_vars = .; __kernel_vars = .;
  /DISCARD/ : { *(.comment* .gnu.linkonce.* .note* .init.data .init.text .eh_frame .ctors .dtors) }
}
