/*
 * flashtest.cc
 */

#define BLOCK_SIZE 16384
#include<iostream>
#include<cstdlib>
#include<cassert>
#include <fcntl.h>
#include<time.h>
using namespace std;
int main(int argc, char *argv[])
{
	assert(argc == 2);
	int fd = creat(argv[1], 0777);
	time_t t1 = time(NULL);
	time(&t1);
	long blocks = (500) * (1024 * 1024 / BLOCK_SIZE);
	long i = 0;
	for (i = 0; i < blocks; i++) {
		char data[BLOCK_SIZE];
		memset(data, '0', BLOCK_SIZE);
		write(fd, data, BLOCK_SIZE);
		fsync(fd);
		cout<<i<<endl;
		if (i == 10000)
			break;
	}

	close(fd);
	time_t t2 = time(NULL);
	time(&t2);
	time_t diff = t2 - t1;
	cout << (diff) << "seconds." << t1 << " " << t2 << " " << i << endl << endl;
}
