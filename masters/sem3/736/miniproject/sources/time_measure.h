#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <unistd.h>
#include <sched.h>
#include <sys/time.h>
#include <time.h>


typedef unsigned long long u64_t;
typedef unsigned long u32_t;

//stolen from http://en.wikipedia.org/wiki/RDTSC
inline u64_t rdtsc()
{
	u32_t lo, hi;
	/*
	* cpuid will serialize the following rdtsc with respect to all other
	* instructions the processor may be handling.
	*/
	__asm__ __volatile__ (
	 "xorl %%eax, %%eax\n"
	 "cpuid\n"
	 "rdtsc\n"
	 : "=a" (lo), "=d" (hi)
	 :
	 : "%ebx", "%ecx");
	return (u64_t)hi << 32 | lo;
}

inline u64_t _one_microsecond()
{
	struct timeval start, end;

	u64_t before = rdtsc();
	gettimeofday(&start,NULL);
	usleep(1000);
	u64_t after = rdtsc();
	gettimeofday(&end,NULL);
	u64_t musecs = end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec);
	return (after - before) / musecs;
}

inline double to_microseconds(u64_t before, u64_t after)
{
	static u64_t one_musecond = _one_microsecond();
	return double(after - before) / one_musecond;
}

inline void set_cpu(int cpu)
{
	cpu_set_t cpuset;
	sched_getaffinity(getpid(),sizeof(cpu_set_t),&cpuset);
	CPU_ZERO(&cpuset);
	CPU_SET(cpu,&cpuset);
	sched_setaffinity(getpid(),sizeof(cpu_set_t),&cpuset);
}

#endif
