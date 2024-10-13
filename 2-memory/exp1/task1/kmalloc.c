#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

unsigned char *kmallocmem1;
unsigned char *kmallocmem2;

static int __init mem_module_init(void)
{
	printk("Start kmalloc!\n");
	kmallocmem1 = (unsigned char *)kmalloc(1024, GFP_KERNEL);
	if (kmallocmem1 != NULL)
	{
		printk(KERN_ALERT "kmallocmem1 addr = %lx\n", (unsigned long)kmallocmem1);
	}
	else
	{
		printk("Failed to allocate kmallocmem1!\n");
	}
	// 请按实验指导书要求补充完整 kmallocmem2 的申请语句
	//
	kmallocmem2 = (unsigned char *)kmalloc(8 * 1024, GFP_KERNEL);
	if (kmallocmem2 != NULL)
	{
		printk(KERN_ALERT "kmallocmem2 addr = %lx\n", (unsigned long)kmallocmem2);
	}
	else
	{
		printk("Failed to allocate kmallocmem2!\n");
	}
	return 0;
}

static void __exit mem_module_exit(void)
{
	kfree(kmallocmem1);
	kfree(kmallocmem2);
	printk("Exit kmalloc!\n");
}

module_init(mem_module_init);
module_exit(mem_module_exit);
