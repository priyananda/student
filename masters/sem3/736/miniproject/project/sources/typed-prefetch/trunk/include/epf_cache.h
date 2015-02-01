#ifndef EPF_CACHE_H
#define EPF_CACHE_H

#include <asm/div64.h>
#include <linux/mm_types.h>
typedef unsigned long long ull_t;

static inline unsigned long long epf_rdtsc()
{
	uint32_t lo, hi;
	__asm__ __volatile__ (
		"xorl %%eax, %%eax\n"
		"cpuid\n"
		"rdtsc\n"
		: "=a" (lo), "=d" (hi)
		:
		: "%ebx", "%ecx"
	);
	return (uint64_t)hi << 32 | lo;
}

//when was the last page evicted
extern ull_t epf_last_page_evicted_ts;

//global average
extern ull_t epf_page_lifetime_longterm;

//local average, for the past 5-10 pages
extern ull_t epf_page_lifetime_shortterm;

struct page;

#define PAGE_HISTORY_SIZE 3

extern int printdebugprftch;

static inline void epf_on_page_evicted(struct page * evicted_page)
{
	static int epf_page_eviction_counter = 1;
	ull_t life;
	ull_t nvg;
	ull_t lavg;
	
	epf_last_page_evicted_ts = epf_rdtsc();
	if ( epf_last_page_evicted_ts < evicted_page->start_ts ||
	     evicted_page->start_ts == 0) {
		printk( KERN_DEBUG
			"PRFTCH_DBG:EC3:Error: lifetime = %llu - %llu\n",
			epf_last_page_evicted_ts, evicted_page->start_ts);
	}else{	
		life = epf_last_page_evicted_ts - evicted_page->start_ts;
		nvg  = epf_page_lifetime_longterm  * epf_page_eviction_counter + life;
		lavg = epf_page_lifetime_shortterm * PAGE_HISTORY_SIZE         + life;

		if(life > 20 * 1000000000)
			return;

		do_div(nvg,epf_page_eviction_counter);
		epf_page_lifetime_longterm = nvg;
		++epf_page_eviction_counter;

		do_div(lavg,PAGE_HISTORY_SIZE);
		epf_page_lifetime_shortterm = lavg;
		
		if(printdebugprftch)
			printk( KERN_DEBUG
				"PRFTCH_DBG:EC1:some page evicted(lifetime = %llu - %llu = %llu)\n",
				epf_last_page_evicted_ts, evicted_page->start_ts, life
			);
     }
}

//min of local and global
static inline ull_t epf_page_lifetime()
{
  return (epf_page_lifetime_longterm < epf_page_lifetime_shortterm) ?
      epf_page_lifetime_longterm : epf_page_lifetime_shortterm;
}

static inline void epf_on_page_access(struct page * page)
{
	if (page == NULL)
		return;
	page->start_ts = epf_rdtsc();
	//if(printdebugprftch)
		//printk(KERN_DEBUGi
		//	"PRFTCH_DBG:EC2:Page Accessed:%llu\n",
		//	page->start_ts
		//);

}
#endif
