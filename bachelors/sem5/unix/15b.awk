#!/bin/gawk -f
BEGIN{
	SUBSEP=" "
}
{
	for ( i = 1 ; i <= NF ; ++i)
		arr[NR,i] = $i;
}
END{
	for ( i = 1 ; i <=NR ; ++i ){
		for ( j = 1 ; j <= NF ; ++j)
			printf arr[j,i] " ";	
		print " ";
	}
}
