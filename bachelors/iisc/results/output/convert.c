#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int get_line(int fd, char * buff){
	int i = 0;
	char ch = 'a';
	while( read(fd,&ch,1) > 0){
		if( !ch || ch == '\n' || ch == '\r' ) break;
		buff[i++] = ch;
	}
	buff[i] = 0 ;
	return i-1;
}
/*
  {LOAD}
  {NUM_RUNNING} {IDLE TICKS}
  {USER}{SYSTEM} {NICE} {TOTAL}
  {NUM_SWITCHES} {JIFFIES}
  {IDLE} {TOTAL} {SCHED CALLS} {HEAVY CON SWTCH}
*/
int main(){
	char buff[255];
	int load;
	unsigned int nrun,itick ;
	unsigned int user,system,nice,total
	unsigned int sw,jf;
	unsigned int idle, tot, sched,heavy;

	int fd = open( "load.txt" , O_RDONLY );
	int out = open ( "grin3.txt" , O_WRONLY | O_CREAT , 0777);

	while(get_line( fd,buff) >= 0 ){
		sscanf( buff,
			"Oink %d ||"
			"%u %u||"
			"%u %u %u %u||"
			"%u %u||"
			"%u %u %u %u",
			&load,
			&nrun,&itick,
			&user, &system,&nice,&total,
			&sw, &jf ,
			&idle,&tot,&sched,&heavy
		);
		sprintf(buff,"%u %f %f %f %u %u %d\n" ,
				nrun,
				((float)user) / total,
				((float)system) / total,
				((float)nice) / total,
				sw,
				jf,
				load,
		);
		write( out, buff,strlen(buff) );
		get_line(fd,buff);
	}
	close(fd);
	close(out);
}
