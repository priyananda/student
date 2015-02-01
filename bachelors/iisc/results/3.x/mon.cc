#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>
#include <fcntl.h>

void get_cpu( char * buff , struct tms * tx)
{
	int itemp; unsigned long ltemp;
	char ctemp[100];
	puts(buff);
	sscanf(buff,
			"%d (%s) %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu \
			%lu %ld %ld" ,
		&itemp,
		ctemp,
		ctemp,
		&itemp,
		&itemp,
		&itemp,
	    &itemp,
		&itemp,
		&ltemp,
		&ltemp,
		&ltemp,
		&ltemp,
		&ltemp,
		&tx->tms_utime,
		&tx->tms_stime,
		&tx->tms_cutime,
		&tx->tms_cstime );
		printf( "Oink :%d %d\n\n" , tx->tms_utime , tx->tms_stime  );
}
int main(int argc , char * argv[]){
	char buff[500];
	sprintf( buff,"/proc/%s/stat" , argv[1]);
	puts(buff);
	int fd = open(buff,O_RDONLY);
	struct tms times;
	int old_val = 0;
	while(1){
		lseek( fd, 0 , SEEK_SET );
		int size = read( fd , buff , 500 );
		buff[size] = 0;
		get_cpu( buff , &times );
		int nval = 	times.tms_utime + times.tms_stime - old_val;
		old_val += nval;
		printf( "Time :%d\n" , nval );
		sleep(1);
	}
	return 0;
}
