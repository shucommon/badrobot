//#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QIANG");
MODULE_DESCRIPTION("chap 3");

static int number = 1;
static char* word = "hi";

module_param(number, int, 0660);
module_param(word, charp, 0660);

MODULE_PARM_DESC(number, "des number");
MODULE_PARM_DESC(word, "des word");

int my_init_module(void)
{
	printk("hello world, number=%d, word=%s\n", number, word);
	return 0;
}

void my_cleanup_module(void)
{
	printk("bye\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);
