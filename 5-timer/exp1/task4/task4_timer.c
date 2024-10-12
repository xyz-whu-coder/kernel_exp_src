#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/mm_types.h>

MODULE_LICENSE("GPL");

static int __init maxPro_init(void)
{
	struct task_struct *p;
	printk("maxPro init\n");
	for_each_process(p){
		// 请按实验指导书要求补充完整 
	}
	return 0;
}

static void __exit maxPro_exit(void)
{
        printk("maxPro exit\n");
}

module_init(maxPro_init);
module_exit(maxPro_exit);
