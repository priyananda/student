#!/bin/gawk -f
BEGIN{
	FS=":";
}
{
	kount[$3]++;
	unames[$3] = unames[$3] "\t" $1;
}
END{
	for ( var in kount ){
		if ( kount[var] > 1 )
			printf "Duplicate :: %s\n",unames[var];
	}
}	
