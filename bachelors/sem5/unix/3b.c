#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc,char * argv[]){
	struct stat stBuff;
	int i;
	if ( argc < 2 ){
		puts("Error :: no arguments ");
		return 0;
	}
	for (  i = 1 ; i < argc ; ++i){
		if (lstat(argv[i],&stBuff) ){
			printf("Error stating file :%s",argv[i]);
			continue;
		}
		if ( S_ISREG(stBuff.st_mode) ){
			printf("%s : Regular File\n",argv[i]);
		}	
		if ( S_ISDIR(stBuff.st_mode) ){
			printf("%s : Directory\n",argv[i]);
		}	
		if ( S_ISLNK(stBuff.st_mode) ){
			printf("%s : Link\n",argv[i]);
		}	
		if ( S_ISSOCK(stBuff.st_mode) ){
			printf("%s : Socket\n",argv[i]);
		}	
		if ( S_ISCHR(stBuff.st_mode) ){
			printf("%s : Character Device\n",argv[i]);
		}	
		if ( S_ISFIFO(stBuff.st_mode) ){
			printf("%s : FIFO pipe\n",argv[i]);
		}	
		if ( S_ISBLK(stBuff.st_mode) ){
			printf("%s : Block Device\n",argv[i]);
		}	
	}	
	return 0;
	
}
