#include <stdio.h>
#include <unistd.h>

unsigned char buffer[8192];

int main(int argc, char * argv[])
{
	int fd = open(argv[1],0);
	int delay = atoi(argv[2]);
	printf("inode : %d\n",fd);
	while( read(fd,buffer,8192) > 0 )
		usleep(delay);
	close(fd);
	return 0;
}
