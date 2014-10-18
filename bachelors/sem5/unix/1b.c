#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	int pid;
	char command[50];
	int ch;
	pid = fork();
	if ( pid == 0 ){
		// In child process
		while(1){
			printf("Enter the command:: ");
			scanf("%s",command);
			system(command);
			fflush(stdin);
			printf("Want to continue?(y/n):\n");
			fflush(stdin);
			ch = getc(stdin);
			ch = getc(stdin);
			ch = getc(stdin);
			printf("Char is %c %d ",ch ,ch);
			if ( ch == 'n' || ch == 'N' )break;
		}
	}else{
		wait(NULL);
	}	
	return 0;
}
