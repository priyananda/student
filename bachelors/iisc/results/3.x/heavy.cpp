#include <iostream>
#include <sys/time.h>
#include <net.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;

volatile int cum_times = 0 , number = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
volatile int thread_count = 0;

void update_times( int time ){
	pthread_mutex_lock( &lock );
	{
		cum_times += time;
		number ++;
	}
	pthread_mutex_unlock( &lock );
}

void * send_request(void * gg){
	Socket s = Socket("localhost",80);
	StringWriter sw ( s.getOutputStream() );
	StringReader sr ( s.getInputStream() );
	struct timeval start,end;
	static char * request =
		"GET /index.html HTTP/1.1\n"
		"Host: oink\n\n";
	gettimeofday( &start , NULL );
	sw.write( request );
	sr.readLine();
	gettimeofday( &end , NULL );
	long long val = 
		(long long)
		( end.tv_sec - start.tv_sec) * 1000000L +
		( end.tv_usec - start.tv_usec);
	update_times( (int) val);
	--thread_count;
}

void delegate_task(){
	pthread_t tid;
	static char ch = 1;
	++thread_count;
	pthread_create( &tid , NULL , send_request , &ch );
}
int main( int argc , char * argv[]){
	for ( int step = 1000 ; step < 1010 ; step += 10 )
	{
		thread_count = 0;
		for( int i = 0 ;i < step ; ++i )
			delegate_task();
		while(thread_count);
		printf("%d %f\n", step,
			   (double) cum_times / (double) number);
		cum_times = number = 0;
	}
	return 0;
}
