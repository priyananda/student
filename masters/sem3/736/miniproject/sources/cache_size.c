#include "time_measure.h"
#include "file_helpers.h"

#include <stdio.h>

#include <string>
#include <list>
using namespace std;


int main(int argc, char * argv[])
{
	--argc;argv++;

	//read a big forwards
	int buffer_size = MEGA_BYTE;
	unsigned char * buffer = new unsigned char[buffer_size];
	
	int fd = ::open(argv[0],O_RDONLY);
	if(fd < 0){
		printf("file not found");
		return 1;
	}

	int size = 0;
	while(true){
		int ret = read(fd,buffer,buffer_size);
		if(ret <= 0)
			break;
		size += ret;
	}
	
	char printbuff[200];
	list<string> messages;
	
	while(size > MEGA_BYTE){
		
		lseek(fd,-buffer_size,SEEK_CUR);
		
		u64_t before = rdtsc();
		read(fd,buffer,buffer_size);
		u64_t after = rdtsc();
		
		sprintf(printbuff,"%d %lf" , size / MEGA_BYTE , to_microseconds(before,after) );
		messages.push_back(printbuff);
		
		lseek(fd,-buffer_size,SEEK_CUR);
		
		size -= buffer_size;
	}
	
	for(list<string>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
		puts((*iter).c_str());

	flush_cache(fd);
	close(fd);

	return 0;
}
