#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/kernel_stat.h>
#include <linux/fdreg.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/smp_lock.h>
#include <linux/init.h>
#include <linux/console.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/mmu_context.h>
#include <asm/semaphore-helper.h>

#include <linux/timex.h>
#include <linux/timer.h>
#include <shenoy/perf.h>

unsigned int 	pp_idle_count  = 0 , 
		pp_total_count = 0 ,
		pp_sched_calls = 0 ,
		pp_heavy_swtch = 0 ;
static int    old_switch = 0;
int pp_load = 0;
static struct timer_list pp_timer = {0};

extern volatile unsigned long jiffies;
extern int do_syslog(int type,char * buff,int len);
extern unsigned long avenrun[];

int __init pp_init(void){
	do_syslog(6,NULL,0);
	init_timer(& pp_timer);
	pp_timer.data = 0;
	pp_timer.function = pp_show_stats;
	pp_timer.expires = 100 + jiffies; // approx 10 to 11 secs
	add_timer(& pp_timer );
	printk( "Initial value of jiffies :" );
	return 0;
}
/*
  {IDLE TICKS} {NUM_RUNNING}
  {USER}{SYSTEM} {NICE} {TOTAL}
  {NUM_SWITCHES} {JIFFIES}
  {IDLE} {TOTAL} {SCHED CALLS} {HEAVY CON SWTCH}
*/
void pp_show_stats(void){
	pp_calc_load();
	printk( KERN_INFO
		"%u %u||"
		"%u %u %u %u||"
		"%u %u||"
		"%u %u %u %u\n",

		jiffies - kstat.cpu_user - kstat.cpu_system,
		nr_running,

		kstat.cpu_user,
		kstat.cpu_system,
		kstat.cpu_nice,
		kstat.cpu_user +
		kstat.cpu_system +
		kstat.cpu_nice,

		kstat.context_swtch - old_switch,
		jiffies,

		pp_idle_count,
		pp_total_count,
		pp_sched_calls,
		pp_heavy_swtch
	);
	old_switch = kstat.context_swtch ; 
	mod_timer( & pp_timer , jiffies + 1000 ); 
	pp_idle_count = pp_total_count = 0;
	pp_sched_calls = pp_heavy_swtch = 0;
}
