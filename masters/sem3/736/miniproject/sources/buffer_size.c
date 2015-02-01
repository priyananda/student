#include "time_measure.h"
#include "file_helpers.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <list>
using namespace std;

int main(int argc, char * argv[])
{
	--argc;++argv;
	
	set_cpu(0);

	int fd = ::open(argv[0],O_RDONLY);
	if(fd < 0){
		printf("file not found");
		return 1;
	}
	
	flush_cache(fd);
	disable_prefetch(fd);
	
	//align it to 16kB boundary. This is unfair because we know that
	//buffer size is 4/8/16kB so taking the lcm of those makes
	//sure of alignment
	int random_file_location = (rand() % 10 + 1) * 16 * KILO_BYTE;
	
	lseek(fd,random_file_location,SEEK_SET);
	
	char printbuff[200];
	list<string> messages;
	
	//start reading in 512 byte chunks
	unsigned char buffer[KILO_BYTE];
	for(int offset = 0; offset < 50 * KILO_BYTE ; offset += 512 ){
		u64_t before = rdtsc();
		read(fd,buffer,512);
		u64_t after = rdtsc();
		if(offset != 0){
			sprintf(printbuff,"%d %lf" , offset , to_microseconds(before,after) );
			messages.push_back(printbuff);
		}
	}
	
	for(list<string>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
		puts((*iter).c_str());
	
	close(fd);
	
	return 0;
}
