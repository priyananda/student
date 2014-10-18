#!/bin/gawk -f
BEGIN{
	
}
{
	if (!line[$0] )
		print $0;
	line[$0] = 1;
}
END{
}
