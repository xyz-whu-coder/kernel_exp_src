#include <linux/module.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");

struct timer_list timer;
static atomic_t flag = ATOMIC_INIT(0);

void print(struct timer_list *timer)
{
	//添加代码，使用原子化操作，设置flag为1
	
	
	printk("hello,world!\n");
}

static int __init timer_init(void)
{
	int count = 0;
	printk("timer init\n");
	timer.expires = jiffies + 10 * HZ;
	timer.function = print;
	add_timer(&timer);
	//添加代码，使用 mod_timer 函数重设定时器的到期时间为当前时间加上 15 秒
	

	while(atomic_read(&flag) == 0){
		//添加代码， 请按实验指导书要求补充完整，使用msleep
		// 
		
		printk("%dth second\n", ++count);
	}
	return 0;
}

static void __exit timer_exit(void)
{
	printk("timer exit\n");
}

module_init(timer_init);
module_exit(timer_exit);
