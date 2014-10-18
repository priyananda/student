#!/bin/gawk -f
BEGIN{
	FS=":";
}
{
	kount[$3]++;users[$3] = $1 "\t" users[$3] ;
}
END{
	for ( x in kount )
		if ( kount[x] > 1 ) print x "\t:\t" users[x] "\n";
}
