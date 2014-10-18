#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char * argv[]){
	int fd,value;
	fd = atoi(argv[1]);
	if ( (value = fcntl(fd,F_GETFL,0)) == -1 )
		return perror("fcntl :"),0;
	value &= O_ACCMODE;
	printf("Readonly flag :: %s\n",value == O_RDONLY ? "set":"unset");
	printf("Write Only flag :: %s\n",value == O_WRONLY ? "set":"unset");
	printf("Read Write flag :: %s\n",value == O_RDWR ? "set":"unset");
	printf("Append flag :: %s\n",value & O_APPEND ? "set":"unset");
	return 0;
}
