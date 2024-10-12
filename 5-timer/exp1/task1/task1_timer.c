#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");

struct timer_list timer;

void print(struct timer_list *timer)
{
	printk("hello,world!\n");
}

static int __init timer_init(void)
{
	// printk("timer init\n");
	// 请按实验指导书要求补充完整
	// 设置定时器超时时间 为当前时间加上 10 秒钟之后的时钟节拍数
	
	//添加定时触发的函数
	
	//添加定时器
}

static void __exit timer_exit(void)
{
	printk("timer exit\n");
}

module_init(timer_init);
module_exit(timer_exit);
