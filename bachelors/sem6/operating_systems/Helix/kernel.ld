OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
SECTIONS
{
	.text 0x10000 :
	{
		*(.text)
		etext = .; _etext = .;
	}
	.data . :
	{
		*(.data)
		*(.bss)
		edata = .; _edata = .;
	}
}
