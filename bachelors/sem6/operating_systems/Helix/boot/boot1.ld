OUTPUT_FORMAT(binary)
ENTRY(start)
SECTIONS
{
	.text 0x0000 :
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
