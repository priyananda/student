#ifndef __SHENOY_PERF_H
#define __SHENOY_PERF_H

extern int  pp_init();
extern void pp_show_stats();
extern void pp_calc_load();

#define PROF_MAX_LOAD 	(2)
#define PROF_MIN_LOAD 	(-2)
#define PROF_RANGE 	4

#define ABS(x)	( (int)( (x) + 0.5f) )  
#define PROF_SCALE(x) \
	-( ABS((x) * PROF_RANGE ) + PROF_MIN_LOAD )
extern signed int 
		pp_load;
extern
unsigned int 	pp_idle_count   , 
		pp_total_count  ,
		pp_sched_calls  ,
		pp_heavy_swtch  ;

#endif
