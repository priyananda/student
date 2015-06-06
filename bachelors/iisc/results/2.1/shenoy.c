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
#include <shenoy/prof.h>

unsigned int 	pp_idle_count  = 0 , 
		pp_total_count = 0;
int	old_switch = 0;
struct timer_list pp_timer = {0};

extern volatile unsigned long jiffies;
extern int do_syslog(int type,char * buff,int len);

int __init pp_init(void){
	do_syslog(6,NULL,0);// set console log level to disable 
	init_timer(& pp_timer);
	pp_timer.data = 0;
	pp_timer.function = &pp_calc_load;
	pp_timer.expires = 1000 + jiffies; // approx 1.x to 3.x secs
	add_timer(& pp_timer );
	return 0;
}
void pp_calc_load(void){
}

