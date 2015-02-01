#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int child[100];
int curr = 0;
int pipe_fd = 0;

void hogger_task(void){
	volatile int x = 100000 , y = 123456 ;
	volatile float z = 123.4576;
	char ch;
	for(;;){
		z = z * (x * 3) + y * 123.445;
		read( pipe_fd , &ch , 1);
	}
}
void spawn_task(){
	int x ;
	x = fork();
	if( x ){
		child[curr++] = x;
		printf("Created %d\n" , x);
	}else 
		hogger_task();
}
void kill_task(int x){
	printf("Killer called\n");
	for (curr = curr - 1; curr >= 0 ; --curr )
		kill( child[curr] , SIGKILL );
	exit(0);
}
int main(int argc , char * argv[]){
	int num,i;
	char ch[100] ;
	for ( i = 0 ; i < 100 ; ++i )
		ch[i] = 'A';
	signal( SIGINT , kill_task);
	pipe_fd = open ("pipe.1" , O_RDWR , 0777 );
	if ( argc < 2 )
		num = 10;
	else
		num = atoi(argv[1]);
	for ( i = 0 ; i < num ; ++i ){
		spawn_task();
		write(pipe_fd ,ch,100);
		sleep(10);
	}
	while(1){
		write(pipe_fd ,ch,10);
	}
	return 0;	
}
