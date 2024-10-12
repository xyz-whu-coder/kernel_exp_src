//Test for installing and removing of module.
#include <linux/init.h> 
#include <linux/module.h> 
#include <linux/kernel.h>
static int __init hello_init(void){
	printk(KERN_INFO "Hi, Module1 is loaded.\n"); 
	return 0;
}

static void __exit hello_exit(void){ 
	//补充：打印指定语句
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
