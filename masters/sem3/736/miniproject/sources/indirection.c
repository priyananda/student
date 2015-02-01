#include "time_measure.h"
#include "file_helpers.h"
#include <stdio.h>

#include <string>
#include <list>
using namespace std;

int main(int argc, char * argv[])
{
	--argc;++argv;
	
	set_cpu(0);

	int fd = ::open(argv[0],O_WRONLY | O_CREAT);
	if(fd < 0){
		printf("file not creatable");
		return 1;
	}
	
	char buffer[4 * KILO_BYTE];
	int size = 0;
	
	char printbuff[200];
	list<string> messages;

	while(size < 100 * KILO_BYTE){
		
		u64_t before = rdtsc();
		write(fd,buffer,4 * KILO_BYTE);
		//fsync(fd);
		u64_t after = rdtsc();
		
		sprintf(printbuff,"%d %lf" , size / KILO_BYTE , to_microseconds(before,after) );
		messages.push_back(printbuff);
		
		size += 4 * KILO_BYTE;
	}
	
	for(list<string>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
		puts((*iter).c_str());
	
	close(fd);
	
	return 0;
}
