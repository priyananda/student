#!/bin/gawk -f
BEGIN{
	split("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec",months," ");
	split(ARGV[1],array,"-");
	max = 31;mm = array[1] + 0;yr = array[3];dd = array[2];
	if ( mm == 4 || mm == 6 || mm ==  9 || mm == 11 ) max = 30;
	if ( mm == 2 ) max = 28;
	if ( !(yr%4) && ((yr%100)||!(yr%400)) && mm == 2)max = 29;
	if ( mm > 12 || dd > max ){
		printf "Invalid date\n";
		exit 0;
	}
	printf "The date is %s %d , %d\n",months[mm],dd,yr;
}
