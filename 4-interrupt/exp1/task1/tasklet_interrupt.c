#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

static int irq;					 			//中断号变量
static char* devname;						//注册中断的设备名
static struct tasklet_struct mytasklet;		//声明tasklet结构体

module_param(irq, int, 0644);				//用户向内核传递irq参数，这里注册的irq号，是一个用户参数
module_param(devname, charp, 0644);		//用户向内核传递devname参数，这里设备名，也是用户要提供的参数

MODULE_LICENSE("GPL");

struct myirq
{
	int devid;
};

struct myirq mydev = {1900};

/* tasklet结构体的处理函数*/
static void mytasklet_handler(unsigned long data)
{
	printk("=== tasklet is working...\n");
}

/*中断处理函数*/
static irqreturn_t myirq_handler(int irq,void* dev)
{
	struct myirq mydev;
	static int count = 0;
	mydev = *(struct myirq*)dev;
	printk("=========================================================================");
	printk("=== count : %d...\n", count + 1);
	printk("=== devid:%d ISR is working...\n", mydev.devid);
	printk("=== Bottom half will start...\n");
	//此处请添加代码，动态初始化tasklet，使用tasklet_init


	//此处请添加代码，调度tasklet，在tasklet被调度以后，只要有机会它就会尽可能早地运行，使用tasklet_schedule


	printk("=== ISR is leaving...\n");
	count++;
	return IRQ_HANDLED;
}

static int __init myirq_init(void)
{
	int req_ret;
	printk("=== Module starts...\n");
	//以共享中断引脚线的方式注册中断号irq与中断设备devname，中断处理函数为myirq_handler
	//
	req_ret = request_irq(irq, myirq_handler, IRQF_SHARED, devname, &mydev);
	printk(KERN_ALERT "=== req_ret is %d\n", req_ret);
	if(req_ret != 0)
	{
		printk("=== %s request IRQ:%d failed...\n", devname, irq);
		return -1;
	}
	else printk("=== %s request IRQ:%d success...\n", devname, irq);
	return 0;
}

static void __exit myirq_exit(void)
{
	printk("=== Module exits...\n");
	tasklet_kill(&mytasklet);
	free_irq(irq,&mydev);
	printk("=== %s request IRQ:%d leaving success...\n",devname,irq);
}

module_init(myirq_init);
module_exit(myirq_exit);

