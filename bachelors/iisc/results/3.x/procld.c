#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct Four {
	unsigned long u , s , cu , cs;
} four_t;

void read_proc( char * pid , four_t * time )
{
	int itemp,a,b,c,d,e,f, fd;
	unsigned long ltemp , m , n , o , p , q;
	char ctemp[100],ch;
	char buff[512];
	
	sprintf(ctemp,"/proc/%s/stat" , pid );
	fd = open ( ctemp , O_RDONLY );
	itemp = read( fd , buff,511 );
	buff[itemp] = 0;
	sscanf( buff,
			"%d (%[^)]) %c %d %d %d %d %d %lu %lu %lu %lu %lu %lu"
			" %lu %ld %ld" ,
		&itemp,
		ctemp,
		&ch,
		&a,
		&b,
		&c,
		&d,
	    &e,
		&m,
		&n,
		&o,
		&p,
		&q,
		&time->u,
		&time->s,
		&time->cu,
		&time->cs );
	close(fd);
}

#define tv2double(tv) \
		(double)tv.tv_sec + \
		(double)tv.tv_usec / 1000000.0;

#define read_time(tv,dval) \
	do{ \
		gettimeofday(&tv,NULL); \
		dval = tv2double(tv); \
	}while(0)

#define read_ptime(str,four,dval) \
	do{ \
		read_proc(str,&four); \
		dval = ((double)four.u + (double)four.s + \
				(double)four.cu + (double)four.cs) \
				/ 100.0f; \
	}while(0)

int main(int argc , char * argv[]){
	struct timeval tv ;
	four_t time = { 0 };
	double total_ticks = 0.0f , told_ticks = 0.0f;
	double proc_ticks[10] = {0.0f}; 
	double pold_ticks[10] = {0.0f};
	read_time(tv,told_ticks);
	for( int i = 0 ; i < argc ; ++i )
		read_ptime(argv[i],time,pold_ticks[i]);

	setbuf(stdout,NULL);	
	while(1){
		read_time(tv,total_ticks);
		for( int i = 1 ; i < argc ; ++i ){
			read_ptime(argv[i],time,proc_ticks[i]);
			printf("%lf " , 
					(proc_ticks[i] - pold_ticks[i]) 
					/ (total_ticks - told_ticks)
			);
			pold_ticks[i] = proc_ticks[i];
		}
		told_ticks = total_ticks;
		puts(" ");
		usleep(500000);
	}
	
	return 0;
}
