#include <linux/mm_types.h>
#include <linux/epf_cache.h>

//var defns
ull_t epf_last_page_evicted_ts = 0;
ull_t epf_page_lifetime_longterm = 0;
ull_t epf_page_lifetime_shortterm = 0;
