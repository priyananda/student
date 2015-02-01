#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int child[100];
int curr = 0;

void hogger_task(void){
	volatile int x = 100000 , y = 123456 ;
	volatile float z = 123.4576;
	for(;;)
		z = z * (x * 3) + y * 123.445;
}
void spawn_task(){
	int x ;
	x = fork();
	if( x ){
		child[curr++] = x;
		printf("Created %d\n" , x);
		sleep(30); // Half Minute
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
	signal( SIGINT , kill_task);
	if ( argc < 2 )
		num = 10;
	else
		num = atoi(argv[1]);
	for ( i = 0 ; i < num ; ++i )
		spawn_task();
	while(1);
	return 0;	
}
