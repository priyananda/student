#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

extern int printdebugprftch;
extern int avi_boost;
extern int use_new_algo;

int print_debug=1;
int new_algo=1;

//MODULE_PARM (print_debug, "i");
//MODULE_PARM (new_algo, "i");
module_param(print_debug, int, 0);
module_param(new_algo, int, 0);

static int __init print_debug_init(void)
{
  printk ("My module worked!\n");
  printdebugprftch=print_debug;
  use_new_algo = new_algo;
  avi_boost = 4;
  return 0;
}

static void __exit print_debug_exit(void)
{
  printk ("Unloading my module.\n");
  printdebugprftch=0;
  use_new_algo=0;
  avi_boost = 1;
  return;
}

module_init(print_debug_init);
module_exit(print_debug_exit);

MODULE_LICENSE("GPL");
