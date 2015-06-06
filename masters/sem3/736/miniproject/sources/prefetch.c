#include "time_measure.h"
#include "file_helpers.h"
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <list>
using namespace std;

//read k MB
//sleep for 10 seconds
//access next 2 MB in 4 kb chunks
int main(int argc, char * argv[])
{
	--argc;argv++;
	
	set_cpu(0);

	int file = open(argv[0],O_RDONLY);
	
	if(file < 0){
		printf("file not found");
		return 1;
	}
	
	flush_cache(file);
	
	int buffer_size = KILO_BYTE;
	int k = atoi(argv[1]);
	unsigned char * buffer = new unsigned char[buffer_size];
	
	int size = 0;
	while( size < k * MEGA_BYTE ){
		read(file,buffer,buffer_size);
		size += buffer_size;
	}
	
	sleep(1);
	
	size = 0;
	char printbuff[200];
	list<string> messages;
	
	buffer_size = 10 * KILO_BYTE;
	delete buffer;
	buffer = new unsigned char[buffer_size];
	
	while(size < MEGA_BYTE ){
		u64_t before = rdtsc();
		int ret = read(file,buffer,buffer_size);
		u64_t after  = rdtsc();
		
		sprintf(printbuff,"%d %lf" , size , to_microseconds(before,after) );
		messages.push_back(printbuff);
		size += ret;
	}
	
		
	for(list<string>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
		puts((*iter).c_str());

	close(file);

	return 0;
}
