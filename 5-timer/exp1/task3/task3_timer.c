#include <linux/module.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/rtc.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

struct timer_list timer;

static int getCurrentTime(void)
{
	// 请按实验指导书要求补充完整 getCurrentTime 函数

	printk("Current time:%d-%02d-%02d %02d:%02d:%02d\n", year, mon, day, hour, min, sec);
	return (int)tv.tv_sec;
}

void print(struct timer_list *timer)
{
	printk("hello,world!\n");
}

static int __init timer_init(void)
{
	printk("timer init\n");
	timer.expires = jiffies + 10 * HZ;
	timer.function = print;
	add_timer(&timer);
	printk("Timer is added.");
	getCurrentTime();
	msleep(8000);
	// 请按实验指导书要求补充完整， 删除timer

	printk("Timer is deleted.");
	getCurrentTime();
	return 0;
}

static void __exit timer_exit(void)
{
	printk("timer exit\n");
}

module_init(timer_init);
module_exit(timer_exit);
