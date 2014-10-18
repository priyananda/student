OUTPUT_FORMAT("coff-go32")
ENTRY(_start)
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
