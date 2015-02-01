#ifndef __SHENOY_PERF_H
#define __SHENOY_PERF_H

extern int  pp_init();
extern void pp_show_stats();
extern void pp_calc_load();

extern
unsigned int 	pp_idle_count   , 
		pp_total_count  ,
		pp_sched_calls  ,
		pp_heavy_swtch  ;

#endif
