#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char * argv[]){
	int i; 
	struct stat stBuff;
	for ( i = 1 ; i < argc ; ++i ){
		if (lstat(argv[i],&stBuff))
		{ perror("Error::");continue;}
		printf("Major Device Number ::%d\n",major(stBuff.st_dev));
		printf("Minor Device Number ::%d\n",minor(stBuff.st_dev));
		if ((S_ISBLK(stBuff.st_mode) || S_ISCHR(stBuff.st_mode))){
			printf("Raw Major Device Number ::%d\n",
					major(stBuff.st_rdev));
			printf("Raw Minor Device Number ::%d\n",
					minor(stBuff.st_rdev));
		}
	}	
	return 0;
}
