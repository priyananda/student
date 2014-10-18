#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/types.h>

int main(int argc,char *argv[]){
	struct tms exTime;
	int pid;
	pid = fork();
	if(pid){
		wait(NULL);
	}else{
		execvp(argv[1],argv+1);
	}
	times(&exTime);
	printf("Time taken ( in ticks ) :%d ",exTime.tms_cutime+
		       	exTime.tms_cstime );
	return 0;
}
