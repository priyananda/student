#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <sys/time.h>

#define SIZE (64 * 1024)

char buffer[SIZE];

void testWrite()
{
	int fd = open("/project/764-usb/test4.dat", O_RDWR | O_CREAT | O_SYNC);
	memset(buffer,'2',SIZE);
	struct timeval start, end;
	int i;
	for(i = 0 ; i < 100; ++i ){
		gettimeofday(&start,0);
		write(fd,buffer,SIZE);
		fsync(fd);
		gettimeofday(&end,0);
		printf("%ld\n", (end.tv_sec * 1000000L + end.tv_usec) - (start.tv_sec * 1000000L + start.tv_usec));
	}
	close(fd);
}

void readRnd()
{
	vector<int> init;
	vector<int> rndz;
	
	for(int i = 0 ; i < 10; ++i)
		init.push_back(i);
	
	while(!init.empty()){
		int ri = rand % init.size();
		rndz.push_back(init[i]);
		init.erase(i);
	}
	
	for(int i = 0 ; i < 10; ++i)
		printf("%d  ", rndz[i]);
	
	return;	
	/*
	for(i = 0 ; i < 10; ++i ){
		lseek(fd,rndz[i] * SIZE,SEEK_SET);
		gettimeofday(&start,0);
		if(read(fd,buffer,SIZE) < 0)
			puts("read filed");
		gettimeofday(&end,0);
		printf("%ld\n", (end.tv_sec * 1000000L + end.tv_usec) - (start.tv_sec * 1000000L + start.tv_usec));
	}
	*/
}

void testRead()
{
	int fd = open("/project/764-usb/test4.dat", O_RDONLY);
	struct timeval start, end;
	int i;

	posix_fadvise(fd,0,0,POSIX_FADV_RANDOM);

	for(i = 0 ; i < 100; ++i ){
		gettimeofday(&start,0);
		if(read(fd,buffer,SIZE) < 0)
			puts("read filed");
		gettimeofday(&end,0);
		printf("%ld\n", (end.tv_sec * 1000000L + end.tv_usec) - (start.tv_sec * 1000000L + start.tv_usec));
	}
	close(fd);
}

int main(int argc, char * argv[])
{
	testRnd();return 0;
	if(argc >= 2)
		testWrite();
	else
		testRead();
}