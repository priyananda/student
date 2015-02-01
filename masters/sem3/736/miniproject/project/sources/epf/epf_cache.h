#ifndef EPF_CACHE_H
#define EPF_CACHE_H

#include <asm/div64.h>

typedef unsigned long long ull_t;

static inline unsigned long long epf_rdtsc()
{
	unsigned int lo, hi;
	__asm__ __volatile__ (
		"xorl %%eax, %%eax\n"
		"cpuid\n"
		"rdtsc\n"
		: "=a" (lo), "=d" (hi)
		:
		: "%ebx", "%ecx"
	);
	return (unsigned long long)hi << 32 | lo;
}

//when was the last page evicted
extern ull_t epf_last_page_evicted_ts;

//global average
extern ull_t epf_page_lifetime_longterm;

//local average, for the past 5-10 pages
extern ull_t epf_page_lifetime_shortterm;

struct page;

static inline void epf_on_page_evicted(struct page * evicted_page)
{
	static int epf_page_eviction_counter = 1;
	ull_t life = epf_last_page_evicted_ts - evicted_page->start_ts;
	ull_t nvg  = epf_page_lifetime_longterm * epf_page_eviction_counter + life;
	
	epf_last_page_evicted_ts = epf_rdtsc();
	do_div(nvg,epf_page_eviction_counter);
	epf_page_lifetime_longterm = nvg;
	++epf_page_eviction_counter;
	
	printk( KERN_DEBUG
		"PRFTCH_DBG:EC1:some page evited(lifetime = %llu)\n",
		life
	);
	//todo: local averages
}

//min of local and global
static inline ull_t epf_page_lifetime()
{
	return epf_page_lifetime_longterm > epf_page_lifetime_shortterm ? epf_page_lifetime_longterm : epf_page_lifetime_shortterm;
}

static inline void epf_on_page_access(struct page * page)
{
	page->start_ts = epf_rdtsc();
}
#endif
