#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int pid;
	pid = fork();
	if(pid){
		printf("+++++++++++++++++++++Parent+++++++++++++++++\n");
		printf("My PID :: %d\n",getpid());
		printf("My kids PID :: %d\n\n",pid);
		wait(0);
	}else{
		printf("+++++++++++++++++++++Child+++++++++++++++++\n");
		printf("My PID :: %d\n",getpid());
		printf("My Parents PID :: %d\n\n",getppid());
	}			
	return 0;
}
