#include <stdio.h>
#include <unistd.h>
#include <ftw.h>
int statFunc(const char * path , struct stat * stbuff,int type){
	if ( type == FTW_F )
		printf("%s : Regular File\n",path);
	if ( type == FTW_D )
		printf("%s : Directory\n",path);
	return 0;
}	
int main(int argc,char * argv[]){
	nftw(argv[1],statFunc,0,0);
	return 0;
}
